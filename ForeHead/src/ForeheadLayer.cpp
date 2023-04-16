#include "ForeheadLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"


namespace Forehead {

	bool ForeheadLayer::OnMouseButtonPressedEvent(IRENE::MouseButtonPressedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnMouseButtonReleasedEvent(IRENE::MouseButtonReleasedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnMouseMovedEvent(IRENE::MouseMovedEvent& e){
		return false;
	}

	bool ForeheadLayer::OnMouseScrolledEvent(IRENE::MouseScrolledEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnKeyPressedEvent(IRENE::KeyPressedEvent& e) {
		IRENE::OrthographicCamera& cam = IRENE::OrthographicCamera::GetCamera();
		switch (e.GetKeyCode()) {
		case IreneKey_W: if (!IRENE::Input::IsKeyPressed(IreneKey_S)) Forehead::s_CameraVelocity.y = -1.0f; return false;
		case IreneKey_A: if (!IRENE::Input::IsKeyPressed(IreneKey_D)) Forehead::s_CameraVelocity.x =  1.0f; return false;
		case IreneKey_S: if (!IRENE::Input::IsKeyPressed(IreneKey_W)) Forehead::s_CameraVelocity.y =  1.0f; return false;
		case IreneKey_D: if (!IRENE::Input::IsKeyPressed(IreneKey_A)) Forehead::s_CameraVelocity.x = -1.0f; return false;
		case IreneKey_R: if (!IRENE::Input::IsKeyPressed(IreneKey_T)) Forehead::s_CameraRotationVelocity =   180.0f; return false;
		case IreneKey_T: if (!IRENE::Input::IsKeyPressed(IreneKey_R)) Forehead::s_CameraRotationVelocity =  -180.0f; return false;
		case IreneKey_Space: cam.Set({ 0.0f, 0.0f, 0.0f }, 0.0f); return false;
		}

		return false;
	}

	bool ForeheadLayer::OnKeyReleasedEvent(IRENE::KeyReleasedEvent& e) {
		IRENE::OrthographicCamera& cam = IRENE::OrthographicCamera::GetCamera();
		switch (e.GetKeyCode()) {
		case IreneKey_W: Forehead::s_CameraVelocity.y = IRENE::Input::IsKeyPressed(IreneKey_S) ?  1.0f : 0.0f; return false;
		case IreneKey_A: Forehead::s_CameraVelocity.x = IRENE::Input::IsKeyPressed(IreneKey_D) ? -1.0f : 0.0f; return false;
		case IreneKey_S: Forehead::s_CameraVelocity.y = IRENE::Input::IsKeyPressed(IreneKey_W) ? -1.0f : 0.0f; return false;
		case IreneKey_D: Forehead::s_CameraVelocity.x = IRENE::Input::IsKeyPressed(IreneKey_A) ?  1.0f : 0.0f; return false;
		case IreneKey_R: Forehead::s_CameraRotationVelocity = IRENE::Input::IsKeyPressed(IreneKey_T) ? -180.0f : 0.0f; return false;
		case IreneKey_T: Forehead::s_CameraRotationVelocity = IRENE::Input::IsKeyPressed(IreneKey_R) ?  180.0f : 0.0f; return false;
		}

		return false;
	}

	bool ForeheadLayer::OnKeyTypedEvent(IRENE::KeyTypedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnWindowResizeEvent(IRENE::WindowResizeEvent& e) {
		return false;
	}

	void ForeheadLayer::OnUpdate(IRENE::DeltaTime dt) {
		IRENE::OrthographicCamera& cam = IRENE::OrthographicCamera::GetCamera();
		cam.Update({ Forehead::s_CameraVelocity.x * dt, Forehead::s_CameraVelocity.y * dt, 0.0f }, Forehead::s_CameraRotationVelocity * dt);
	}
}