#include "ipch.h"

#include "Application.h"
#include "GLFW/glfw3.h"

#include "Keycode/KeycodeToGLFW.h"
#include "Input.h"

namespace Rapier {
	// Implement ifdef based on platform

	bool l_BlockKey = false;
	bool l_BlockMouse = false;

	char l_MouseHeldFlags = 0;

	// Flags
	// 0 : Mouse Left
	// 1 : Mouse Right
	// 2 : Mouse Middle

	//RapierKey_MouseLeft, RapierKey_MouseRight, RapierKey_MouseMiddle, RapierKey_MouseX1, RapierKey_MouseX2, RapierKey_MouseWheelX, RapierKey_MouseWheelY,

	void Input::OnUpdate() {
		
		if (IsMouseButtonPressed(RapierKey_MouseLeft))
			l_MouseHeldFlags |= 0b00000001;
		else
			l_MouseHeldFlags &= 0b11111110;

		if (IsMouseButtonPressed(RapierKey_MouseRight))
			l_MouseHeldFlags |= 0b00000010;
		else
			l_MouseHeldFlags &= 0b11111101;

		if (IsMouseButtonPressed(RapierKey_MouseMiddle))
			l_MouseHeldFlags |= 0b00000100;
		else
			l_MouseHeldFlags &= 0b11111011;

	}

	bool Input::IsKeyPressed(int keycode) {
		if (l_BlockKey)
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetKey(wnd, Key_RapierToGLFW(keycode));
		return pressed == GLFW_PRESS || pressed == GLFW_REPEAT;
	}

	// Bugged ?
	bool Input::IsKeyRepeat(int keycode) {
		if (l_BlockKey)
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetKey(wnd, Key_RapierToGLFW(keycode));
		return pressed == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button) {
		if (l_BlockMouse)
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetMouseButton(wnd, Key_RapierToGLFW(button));
		return pressed == GLFW_PRESS;
	}

	bool Input::IsMouseButtonRepeat(int button) {
		if (l_BlockMouse)
			return false;

		switch (button)
		{
		case RapierKey_MouseLeft   : return l_MouseHeldFlags & 0b00000001;
		case RapierKey_MouseRight  : return l_MouseHeldFlags & 0b00000010;
		case RapierKey_MouseMiddle : return l_MouseHeldFlags & 0b00000100;
		}

		return false;
	}

	glm::vec2 Input::GetMousePos() {
		// input block ?


		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		double x, y;
		glfwGetCursorPos(wnd, &x, &y);

		return { (float)x, (float)y };
	}

	void Input::SetBlockKeyInput(bool enable) {
		l_BlockKey = enable;
	}

	void Input::SetBlockMouseInput(bool enable) {
		l_BlockMouse = enable;
	}
}