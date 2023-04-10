#include "ipch.h"
#include "WindowsInput.h"

#include "Application.h"
#include "GLFW/glfw3.h"

namespace IRENE {

	Input* Input::s_Instance = new WindowsInput();


	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetKey(wnd, keycode);
		return pressed == GLFW_PRESS || pressed == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		int pressed = glfwGetMouseButton(wnd, button);
		return pressed == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		double x, y;
		glfwGetCursorPos(wnd, &x, &y);

		return { (float)x, (float)y };
	}

}