#include "ipch.h"

#include "Application.h"
#include "GLFW/glfw3.h"

#include "Keycode/KeycodeToGLFW.h"
#include "Input.h"

namespace Rapier {
	// Implement ifdef based on platform

	bool l_BlockKey = false;
	bool l_BlockMouse = false;

	bool Input::IsKeyPressed(int keycode) {
		if (l_BlockKey)
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetKey(wnd, Key_RapierToGLFW(keycode));
		return pressed == GLFW_PRESS || pressed == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button) {
		if (l_BlockMouse)
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetMouseButton(wnd, Key_RapierToGLFW(button));
		return pressed == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos() {
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