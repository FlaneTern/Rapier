#pragma once

#include "Camera/Camera.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Time/DeltaTime.h"

namespace Rapier {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio = 16.0f / 9.0f, bool rotation = false)
			: m_AspectRatio(aspectRatio), m_EnableRotation(rotation), 
			  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {}

		virtual void OnUpdate(DeltaTime dt);
		virtual void OnEvent(Event& event);


		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		bool m_EnableRotation;

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }


	protected:
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio;

		const glm::vec3 m_DefaultTranslationSpeed = { 1.5f, 1.5f, 0.0f };
		const float m_DefaultRotationSpeed = 180.0f;

		glm::vec3 m_CameraTranslationSpeed = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotationSpeed = 0.0f;

		OrthographicCamera m_Camera;


		virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		virtual bool OnMouseMovedEvent(MouseMovedEvent& e);
		virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		virtual bool OnKeyPressedEvent(KeyPressedEvent& e);
		virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		virtual bool OnKeyTypedEvent(KeyTypedEvent& e);
		virtual bool OnWindowResizeEvent(WindowResizeEvent& e);
	};
}
