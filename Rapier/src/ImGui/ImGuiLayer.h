#pragma once
#include "Layer.h"


namespace Rapier {

	class RAPIER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(Event& event) override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	protected:
		virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) override;
		virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) override;
		virtual bool OnMouseMovedEvent(MouseMovedEvent& e) override;
		virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e) override;
		virtual bool OnKeyPressedEvent(KeyPressedEvent& e) override;
		virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e) override;
		virtual bool OnKeyTypedEvent(KeyTypedEvent& e) override;
		virtual bool OnWindowResizeEvent(WindowResizeEvent& e) override;

		float dt;
	};
}

