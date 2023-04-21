#include "Layer/BackgroundLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace Forehead {

	static float width = 1.0f;
	static float height = 1.0f;
	static float x = 0.0f;
	static float y = 0.0f;

	void BackgroundLayer::OnUpdate(Rapier::DeltaTime dt) {

		//Rapier::Renderer2D::DrawQuad({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		//Rapier::Renderer2D::DrawQuad({  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
		//Rapier::Renderer2D::DrawQuad({ -1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		//Rapier::Renderer2D::DrawQuad({  1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f });
		
		Rapier::Renderer2D::DrawCircle({ x, y, 0.0f }, { width, height }, { 0.4f, 0.5f, 0.0f, 1.0f });
	}

	void BackgroundLayer::OnAttach() {

	}

	void BackgroundLayer::OnImGuiRender() {
		ImGui::Begin("Background");
		ImGui::SliderFloat("width", &width, 0.0f, 3.0f);
		ImGui::SliderFloat("height", &height, 0.0f, 3.0f);
		ImGui::SliderFloat("x", &x, -3.0f, 3.0f);
		ImGui::SliderFloat("y", &y, -3.0f, 3.0f);
		ImGui::End();
	}

	bool BackgroundLayer::OnMouseButtonPressedEvent(Rapier::MouseButtonPressedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnMouseButtonReleasedEvent(Rapier::MouseButtonReleasedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnMouseMovedEvent(Rapier::MouseMovedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnMouseScrolledEvent(Rapier::MouseScrolledEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnKeyPressedEvent(Rapier::KeyPressedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnKeyTypedEvent(Rapier::KeyTypedEvent& e) {
		return false;
	}

	bool BackgroundLayer::OnWindowResizeEvent(Rapier::WindowResizeEvent& e) {
		return false;
	}

}