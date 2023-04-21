#include "Layer/ForeheadLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace Forehead {

	static float width = 1.0f;
	static float height = 1.0f;
	static float x = 0.0f;
	static float y = 0.0f;

	void ForeheadLayer::OnUpdate(Rapier::DeltaTime dt) {

		Rapier::Renderer2D::DrawTexture({ x, y, 0.0f }, { width, height }, Rapier::AssetManager::DefaultTexture2DId::IreneGyatekora3);

	}

	void ForeheadLayer::OnImGuiRender() {
		ImGui::Begin("Forehead");
		ImGui::SliderFloat("width", &width, 0.0f, 3.0f);
		ImGui::SliderFloat("height", &height, 0.0f, 3.0f);
		ImGui::SliderFloat("x", &x, -3.0f, 3.0f);
		ImGui::SliderFloat("y", &y, -3.0f, 3.0f);
		ImGui::End();
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