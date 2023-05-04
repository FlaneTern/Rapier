#pragma once
#include "Rapier.h"

#include "Layer/Gui/EntityListPanel.h"
#include "Layer/Gui/AssetPanel.h"
#include "LanternCamera.h"

namespace Rapier {

	class LanternLayer : public Layer {
	public:
		LanternLayer()
			: Layer("Lantern"), m_ScriptPath("D:\\C++\\PersonalProjects\\Rapier\\bin\\Debug-x86_64\\RapierLantern\\Forehead.dll") {}

		void OnUpdate(DeltaTime dt) override;
		void OnAttach() override;
		void OnImGuiRender() override;


		void OnEvent(Rapier::Event& event) override {
			Rapier::EventDispatcher dispatcher(event);


			dispatcher.Dispatch<Rapier::MouseButtonPressedEvent>(BIND_EVENT_FN(LanternLayer::OnMouseButtonPressedEvent));
			dispatcher.Dispatch<Rapier::MouseButtonReleasedEvent>(BIND_EVENT_FN(LanternLayer::OnMouseButtonReleasedEvent));
			dispatcher.Dispatch<Rapier::MouseMovedEvent>(BIND_EVENT_FN(LanternLayer::OnMouseMovedEvent));
			dispatcher.Dispatch<Rapier::MouseScrolledEvent>(BIND_EVENT_FN(LanternLayer::OnMouseScrolledEvent));
			dispatcher.Dispatch<Rapier::KeyPressedEvent>(BIND_EVENT_FN(LanternLayer::OnKeyPressedEvent));
			dispatcher.Dispatch<Rapier::KeyReleasedEvent>(BIND_EVENT_FN(LanternLayer::OnKeyReleasedEvent));
			dispatcher.Dispatch<Rapier::KeyTypedEvent>(BIND_EVENT_FN(LanternLayer::OnKeyTypedEvent));
			dispatcher.Dispatch<Rapier::WindowResizeEvent>(BIND_EVENT_FN(LanternLayer::OnWindowResizeEvent));


		}

	private:

		void NewScene();
		void SaveScene();
		void LoadScene();

		void CalculateMousePos();
		void SelectEntity();

		void PlayScene();
		void PauseScene();
		void StopScene();

		void OnUpdateGizmos(DeltaTime dt);

		void LoadScript();
		void SetScriptPath();

		virtual bool OnMouseButtonPressedEvent(Rapier::MouseButtonPressedEvent& e) override;
		virtual bool OnMouseButtonReleasedEvent(Rapier::MouseButtonReleasedEvent& e) override;
		virtual bool OnMouseMovedEvent(Rapier::MouseMovedEvent& e) override;
		virtual bool OnMouseScrolledEvent(Rapier::MouseScrolledEvent& e) override;
		virtual bool OnKeyPressedEvent(Rapier::KeyPressedEvent& e) override;
		virtual bool OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) override;
		virtual bool OnKeyTypedEvent(Rapier::KeyTypedEvent& e) override;
		virtual bool OnWindowResizeEvent(Rapier::WindowResizeEvent& e) override;


		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportPanelSize = { 0.0f,0.0f };
		glm::vec2 m_ViewportMinBound;
		glm::vec2 m_ViewportMousePos;
		glm::vec2 m_SceneMousePos;

		bool m_MainViewportFocused = false;
		bool m_MainViewportHovered = false;

		Ref<Scene> m_ActiveScene = nullptr;
		Ref<Scene> m_RuntimeScene = nullptr;

		Ref<EntityListPanel> m_EntityListPanel;
		Ref<AssetPanel> m_AssetPanel;

		LanternCamera m_LanternCamera;

		int m_HoveredEntityId = -1;

		std::string m_ScriptPath;


		enum class SceneState {
			Edit,
			Pause,
			Runtime
		};


		SceneState m_SceneState;
	};
}

