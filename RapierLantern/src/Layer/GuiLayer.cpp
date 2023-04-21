#include "Layer/GuiLayer.h"
#include "Geometry/Pentagon.h"
#include "RapierLantern.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

#include "entt.hpp"

namespace Rapier {

	void GuiLayer::OnUpdate(DeltaTime dt) {
		
	}

	void GuiLayer::OnAttach() {
		m_ActiveScene = Application::Get().m_ActiveScene;

		m_EntityListPanel = std::make_shared<EntityListPanel>(m_ActiveScene);
	}

	void GuiLayer::OnImGuiRender() {
		m_EntityListPanel->OnImGuiRender();
	}

	bool GuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		return false;
	}

	bool GuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		return false;
	}

	bool GuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		return false;
	}

	bool GuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		return false;
	}

	bool GuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
		return false;
	}

	bool GuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		return false;
	}

	bool GuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		return false;
	}

	bool GuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
		return false;
	}

}