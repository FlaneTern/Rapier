#include "ForeheadLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"


namespace Forehead {

	bool ForeheadLayer::OnMouseButtonPressedEvent(Rapier::MouseButtonPressedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnMouseButtonReleasedEvent(Rapier::MouseButtonReleasedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnMouseMovedEvent(Rapier::MouseMovedEvent& e){
		return false;
	}

	bool ForeheadLayer::OnMouseScrolledEvent(Rapier::MouseScrolledEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnKeyPressedEvent(Rapier::KeyPressedEvent& e) {
		Rapier::OrthographicCamera& cam = Rapier::OrthographicCamera::GetCamera();
		switch (e.GetKeyCode()) {
		case RapierKey_W: if (!Rapier::Input::IsKeyPressed(RapierKey_S)) Forehead::s_CameraVelocity.y =  1.0f; return false;
		case RapierKey_A: if (!Rapier::Input::IsKeyPressed(RapierKey_D)) Forehead::s_CameraVelocity.x = -1.0f; return false;
		case RapierKey_S: if (!Rapier::Input::IsKeyPressed(RapierKey_W)) Forehead::s_CameraVelocity.y = -1.0f; return false;
		case RapierKey_D: if (!Rapier::Input::IsKeyPressed(RapierKey_A)) Forehead::s_CameraVelocity.x =  1.0f; return false;
		case RapierKey_R: if (!Rapier::Input::IsKeyPressed(RapierKey_T)) Forehead::s_CameraRotationVelocity =   180.0f; return false;
		case RapierKey_T: if (!Rapier::Input::IsKeyPressed(RapierKey_R)) Forehead::s_CameraRotationVelocity =  -180.0f; return false;
		case RapierKey_Space: cam.Set({ 0.0f, 0.0f, 0.0f }, 0.0f); return false;
		}

		return false;
	}

	bool ForeheadLayer::OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) {
		Rapier::OrthographicCamera& cam = Rapier::OrthographicCamera::GetCamera();
		switch (e.GetKeyCode()) {
		case RapierKey_W: Forehead::s_CameraVelocity.y = Rapier::Input::IsKeyPressed(RapierKey_S) ? -1.0f : 0.0f; return false;
		case RapierKey_A: Forehead::s_CameraVelocity.x = Rapier::Input::IsKeyPressed(RapierKey_D) ?  1.0f : 0.0f; return false;
		case RapierKey_S: Forehead::s_CameraVelocity.y = Rapier::Input::IsKeyPressed(RapierKey_W) ?  1.0f : 0.0f; return false;
		case RapierKey_D: Forehead::s_CameraVelocity.x = Rapier::Input::IsKeyPressed(RapierKey_A) ? -1.0f : 0.0f; return false;
		case RapierKey_R: Forehead::s_CameraRotationVelocity = Rapier::Input::IsKeyPressed(RapierKey_T) ? -180.0f : 0.0f; return false;
		case RapierKey_T: Forehead::s_CameraRotationVelocity = Rapier::Input::IsKeyPressed(RapierKey_R) ?  180.0f : 0.0f; return false;
		}

		return false;
	}

	bool ForeheadLayer::OnKeyTypedEvent(Rapier::KeyTypedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnWindowResizeEvent(Rapier::WindowResizeEvent& e) {
		return false;
	}

	void ForeheadLayer::OnUpdate(Rapier::DeltaTime dt) {
		Rapier::OrthographicCamera& cam = Rapier::OrthographicCamera::GetCamera();
		cam.Update({ Forehead::s_CameraVelocity.x * dt, Forehead::s_CameraVelocity.y * dt, 0.0f }, Forehead::s_CameraRotationVelocity * dt);
	}
}