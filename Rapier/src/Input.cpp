#include "ipch.h"

#include "Application.h"
#include "GLFW/glfw3.h"

#include "Keycode/KeycodeToGLFW.h"
#include "Input.h"

namespace Rapier {
	// Implement ifdef based on platform

	bool l_Blocked = false;

	bool Input::IsKeyPressed(int keycode) {
		if (l_Blocked) 
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetKey(wnd, Key_RapierToGLFW(keycode));
		return pressed == GLFW_PRESS || pressed == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button) {
		if (l_Blocked) 
			return false;

		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetMouseButton(wnd, button);
		return pressed == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos() {
		// input block ?


		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		double x, y;
		glfwGetCursorPos(wnd, &x, &y);

		return { (float)x, (float)y };
	}

	void Input::BlockInput() {
		l_Blocked = true;
	}

	void Input::UnblockInput() {
		l_Blocked = false;
	}
}