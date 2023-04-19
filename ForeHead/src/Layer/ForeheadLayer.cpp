#include "Layer/ForeheadLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace Forehead {

	void ForeheadLayer::OnUpdate(Rapier::DeltaTime dt) {

		Rapier::Renderer2D::DrawTexture({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, Rapier::AssetManager::DefaultTexture2DId::IreneGyatekora3);

	}

	void ForeheadLayer::OnImGuiRender() {

	}

	void ForeheadLayer::OnAttach() {
		
	}

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
		return false;
	}

	bool ForeheadLayer::OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnKeyTypedEvent(Rapier::KeyTypedEvent& e) {
		return false;
	}

	bool ForeheadLayer::OnWindowResizeEvent(Rapier::WindowResizeEvent& e) {
		return false;
	}

}