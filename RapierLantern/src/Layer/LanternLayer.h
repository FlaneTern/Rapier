#pragma once
#include "Rapier.h"

namespace Rapier {

	class LanternLayer : public Layer {
	public:
		LanternLayer()
			: Layer("Lantern") {}

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

		virtual bool OnMouseButtonPressedEvent(Rapier::MouseButtonPressedEvent& e) override;
		virtual bool OnMouseButtonReleasedEvent(Rapier::MouseButtonReleasedEvent& e) override;
		virtual bool OnMouseMovedEvent(Rapier::MouseMovedEvent& e) override;
		virtual bool OnMouseScrolledEvent(Rapier::MouseScrolledEvent& e) override;
		virtual bool OnKeyPressedEvent(Rapier::KeyPressedEvent& e) override;
		virtual bool OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) override;
		virtual bool OnKeyTypedEvent(Rapier::KeyTypedEvent& e) override;
		virtual bool OnWindowResizeEvent(Rapier::WindowResizeEvent& e) override;

		Ref<Framebuffer> m_Framebuffer;
		Ref<Texture2D> m_Texture;

		glm::vec2 m_ViewportPanelSize = { 0.0f,0.0f };

		bool m_MainViewportFocused = false;
		bool m_MainViewportHovered = false;

		Ref<Scene> m_ActiveScene = nullptr;

	};
}
