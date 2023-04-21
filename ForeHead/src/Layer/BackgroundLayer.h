#pragma once
#include "Rapier.h"

namespace Forehead {

	class BackgroundLayer : public Rapier::Layer {
	public:
		BackgroundLayer()
			: Layer("Background") {}

		void OnUpdate(Rapier::DeltaTime dt) override;
		void OnAttach() override;
		void OnImGuiRender() override;


		void OnEvent(Rapier::Event& event) override {
			Rapier::EventDispatcher dispatcher(event);

			dispatcher.Dispatch<Rapier::MouseButtonPressedEvent>(BIND_EVENT_FN(BackgroundLayer::OnMouseButtonPressedEvent));
			dispatcher.Dispatch<Rapier::MouseButtonReleasedEvent>(BIND_EVENT_FN(BackgroundLayer::OnMouseButtonReleasedEvent));
			dispatcher.Dispatch<Rapier::MouseMovedEvent>(BIND_EVENT_FN(BackgroundLayer::OnMouseMovedEvent));
			dispatcher.Dispatch<Rapier::MouseScrolledEvent>(BIND_EVENT_FN(BackgroundLayer::OnMouseScrolledEvent));
			dispatcher.Dispatch<Rapier::KeyPressedEvent>(BIND_EVENT_FN(BackgroundLayer::OnKeyPressedEvent));
			dispatcher.Dispatch<Rapier::KeyReleasedEvent>(BIND_EVENT_FN(BackgroundLayer::OnKeyReleasedEvent));
			dispatcher.Dispatch<Rapier::KeyTypedEvent>(BIND_EVENT_FN(BackgroundLayer::OnKeyTypedEvent));
			dispatcher.Dispatch<Rapier::WindowResizeEvent>(BIND_EVENT_FN(BackgroundLayer::OnWindowResizeEvent));
		}

		virtual bool OnMouseButtonPressedEvent(Rapier::MouseButtonPressedEvent& e) override;
		virtual bool OnMouseButtonReleasedEvent(Rapier::MouseButtonReleasedEvent& e) override;
		virtual bool OnMouseMovedEvent(Rapier::MouseMovedEvent& e) override;
		virtual bool OnMouseScrolledEvent(Rapier::MouseScrolledEvent& e) override;
		virtual bool OnKeyPressedEvent(Rapier::KeyPressedEvent& e) override;
		virtual bool OnKeyReleasedEvent(Rapier::KeyReleasedEvent& e) override;
		virtual bool OnKeyTypedEvent(Rapier::KeyTypedEvent& e) override;
		virtual bool OnWindowResizeEvent(Rapier::WindowResizeEvent& e) override;

	};
}
