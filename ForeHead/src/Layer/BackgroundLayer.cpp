#include "Layer/BackgroundLayer.h"
#include "Geometry/Pentagon.h"
#include "Forehead.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Forehead {

	void BackgroundLayer::OnUpdate(Rapier::DeltaTime dt) {

		Rapier::Renderer2D::DrawQuad({ -1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		Rapier::Renderer2D::DrawQuad({  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
		Rapier::Renderer2D::DrawQuad({ -1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		Rapier::Renderer2D::DrawQuad({  1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f });
		
	}

	void BackgroundLayer::OnAttach() {

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