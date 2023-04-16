#pragma once
#include "Irene.h"

namespace Forehead {

	class ForeheadLayer : public IRENE::Layer {
	public:
		ForeheadLayer()
			: Layer("Forehead") {}

		void OnUpdate(IRENE::DeltaTime dt) override;

		void OnEvent(IRENE::Event& event) override {
			IRENE::EventDispatcher dispatcher(event);

			dispatcher.Dispatch<IRENE::MouseButtonPressedEvent>(BIND_EVENT_FN(ForeheadLayer::OnMouseButtonPressedEvent));
			dispatcher.Dispatch<IRENE::MouseButtonReleasedEvent>(BIND_EVENT_FN(ForeheadLayer::OnMouseButtonReleasedEvent));
			dispatcher.Dispatch<IRENE::MouseMovedEvent>(BIND_EVENT_FN(ForeheadLayer::OnMouseMovedEvent));
			dispatcher.Dispatch<IRENE::MouseScrolledEvent>(BIND_EVENT_FN(ForeheadLayer::OnMouseScrolledEvent));
			dispatcher.Dispatch<IRENE::KeyPressedEvent>(BIND_EVENT_FN(ForeheadLayer::OnKeyPressedEvent));
			dispatcher.Dispatch<IRENE::KeyReleasedEvent>(BIND_EVENT_FN(ForeheadLayer::OnKeyReleasedEvent));
			dispatcher.Dispatch<IRENE::KeyTypedEvent>(BIND_EVENT_FN(ForeheadLayer::OnKeyTypedEvent));
			dispatcher.Dispatch<IRENE::WindowResizeEvent>(BIND_EVENT_FN(ForeheadLayer::OnWindowResizeEvent));
		}

		virtual bool OnMouseButtonPressedEvent(IRENE::MouseButtonPressedEvent& e) override;
		virtual bool OnMouseButtonReleasedEvent(IRENE::MouseButtonReleasedEvent& e) override;
		virtual bool OnMouseMovedEvent(IRENE::MouseMovedEvent& e) override;
		virtual bool OnMouseScrolledEvent(IRENE::MouseScrolledEvent& e) override;
		virtual bool OnKeyPressedEvent(IRENE::KeyPressedEvent& e) override;
		virtual bool OnKeyReleasedEvent(IRENE::KeyReleasedEvent& e) override;
		virtual bool OnKeyTypedEvent(IRENE::KeyTypedEvent& e) override;
		virtual bool OnWindowResizeEvent(IRENE::WindowResizeEvent& e) override;
	};
}
