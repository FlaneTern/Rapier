#pragma once

#include "Event.h"

namespace Rapier 
{

	class RAPIER_API KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode)
			: m_KeyCode(keyCode) {}

		int m_KeyCode; 
		

	};

	class RAPIER_API KeyPressedEvent : public KeyEvent 
	{
	public:
		KeyPressedEvent(int keyCode, int scanCode, int repeatCount)
			: KeyEvent(keyCode), m_ScanCode(scanCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		inline int GetScanCode() const { return m_ScanCode; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_ScanCode;
		int m_RepeatCount;
	};




	class RAPIER_API KeyReleasedEvent : public KeyEvent 
	{
	public:
		KeyReleasedEvent(int keyCode, int scanCode)
			: KeyEvent(keyCode), m_ScanCode(scanCode) {}

		inline int GetScanCode() const { return m_ScanCode; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyReleased)
	private:
		int m_ScanCode;
	};

	class RAPIER_API KeyTypedEvent : public KeyEvent 
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}


		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	};

}