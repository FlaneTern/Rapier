#pragma once
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Time/DeltaTime.h"


namespace Rapier 
{

	class RAPIER_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(DeltaTime dt) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) = 0;
		virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) = 0;
		virtual bool OnMouseMovedEvent(MouseMovedEvent& e) = 0;
		virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e) = 0;
		virtual bool OnKeyPressedEvent(KeyPressedEvent& e) = 0;
		virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e) = 0;
		virtual bool OnKeyTypedEvent(KeyTypedEvent& e) = 0;
		virtual bool OnWindowResizeEvent(WindowResizeEvent& e) = 0;

	private:
		std::string m_DebugName;
	};
}

