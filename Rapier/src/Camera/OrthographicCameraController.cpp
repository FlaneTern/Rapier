#include "ipch.h"
#include "OrthographicCameraController.h"
#include "Keycode/RapierKeycode.h"
#include "Input.h"

namespace Rapier {

	void OrthographicCameraController::OnUpdate(DeltaTime dt) {
		m_CameraPosition += m_CameraTranslationSpeed * (float)dt * m_ZoomLevel;
		m_Camera.SetPosition(m_CameraPosition);

		if (m_EnableRotation) {
			m_CameraRotation += m_CameraRotationSpeed * (float)dt;
			m_Camera.SetRotation(m_CameraRotation);
		}


		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResizeEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnKeyReleasedEvent));

		//dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonPressedEvent));
		//dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonReleasedEvent));
		//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseMovedEvent));
		//dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(OrthographicCameraController::OnKeyTypedEvent));
	}


	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.GetYOffset() * 0.25;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResizeEvent(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnKeyPressedEvent(KeyPressedEvent& e) {
		switch (e.GetKeyCode()) {
		case RapierKey_UpArrow:    if (!Rapier::Input::IsKeyPressed(RapierKey_DownArrow))  m_CameraTranslationSpeed.y =  m_DefaultTranslationSpeed.y; return false;
		case RapierKey_LeftArrow:  if (!Rapier::Input::IsKeyPressed(RapierKey_RightArrow)) m_CameraTranslationSpeed.x = -m_DefaultTranslationSpeed.x; return false;
		case RapierKey_DownArrow:  if (!Rapier::Input::IsKeyPressed(RapierKey_UpArrow))    m_CameraTranslationSpeed.y = -m_DefaultTranslationSpeed.y; return false;
		case RapierKey_RightArrow: if (!Rapier::Input::IsKeyPressed(RapierKey_LeftArrow))  m_CameraTranslationSpeed.x =  m_DefaultTranslationSpeed.x; return false;
		case RapierKey_O:          if (!Rapier::Input::IsKeyPressed(RapierKey_P))          m_CameraRotationSpeed      =  m_DefaultRotationSpeed;      return false;
		case RapierKey_P:          if (!Rapier::Input::IsKeyPressed(RapierKey_O))          m_CameraRotationSpeed      = -m_DefaultRotationSpeed;      return false;
		}

		return false;
	}

	bool OrthographicCameraController::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		switch (e.GetKeyCode()) {
		case RapierKey_UpArrow:    m_CameraTranslationSpeed.y = Rapier::Input::IsKeyPressed(RapierKey_DownArrow)  ? -m_DefaultTranslationSpeed.y : 0.0f; return false;
		case RapierKey_LeftArrow:  m_CameraTranslationSpeed.x = Rapier::Input::IsKeyPressed(RapierKey_RightArrow) ?  m_DefaultTranslationSpeed.x : 0.0f; return false;
		case RapierKey_DownArrow:  m_CameraTranslationSpeed.y = Rapier::Input::IsKeyPressed(RapierKey_UpArrow)    ?  m_DefaultTranslationSpeed.y : 0.0f; return false;
		case RapierKey_RightArrow: m_CameraTranslationSpeed.x = Rapier::Input::IsKeyPressed(RapierKey_LeftArrow)  ? -m_DefaultTranslationSpeed.x : 0.0f; return false;
		case RapierKey_O:          m_CameraRotationSpeed      = Rapier::Input::IsKeyPressed(RapierKey_P)          ? -m_DefaultRotationSpeed      : 0.0f; return false;
		case RapierKey_P:          m_CameraRotationSpeed      = Rapier::Input::IsKeyPressed(RapierKey_O)          ?  m_DefaultRotationSpeed      : 0.0f; return false;
		}
		return false;
	}




	bool OrthographicCameraController::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		return false;
	}

	bool OrthographicCameraController::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		return false;
	}

	bool OrthographicCameraController::OnMouseMovedEvent(MouseMovedEvent& e) {
		return false;
	}


	bool OrthographicCameraController::OnKeyTypedEvent(KeyTypedEvent& e) {
		return false;
	}
}