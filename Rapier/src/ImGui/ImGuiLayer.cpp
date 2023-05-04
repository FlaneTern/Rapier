#include "ipch.h"

#include "imgui.h"
#include "Imgui/build/imgui_impl_opengl3.h"

#include "Imgui/build/imgui_impl_glfw.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "ImGuiLayer.h"

#include "PerformanceStats.h"


#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include "Keycode/KeycodeToImGui.h"



namespace Rapier {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {	}

	ImGuiLayer::~ImGuiLayer() {

	} 

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		RAPIER_CORE_INFO("{0}", glfwGetVersionString());
		Application::Get().m_ImGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)app.GetWindow().GetPlatformWindow(), false);
		ImGui_ImplOpenGL3_Init("#version 410");

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate(DeltaTime dt) {
		this->dt = dt;
	}

	void ImGuiLayer::OnImGuiRender() {
		static bool show = true;
		ImGui::Begin("Stats", &show);

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

		ImGui::Separator();
		bool fd_node_open = ImGui::TreeNodeEx("Frame Stats", base_flags, "Frame Stats");
		if (fd_node_open) {
			auto& frameData = PerformanceStats::s_CurrentFrameData;
			ImGui::Separator();
			for (const auto& funcTime : frameData.FunctionTime) {
				ImGui::Text("%s : %f ms", funcTime.FunctionName.c_str(), funcTime.FunctionTimeMS);
			}
			ImGui::TreePop();
		}

		ImGui::Separator();

		bool rd_node_open = ImGui::TreeNodeEx("Renderer Stats", base_flags, "Renderer Stats");
		if (rd_node_open) {
			auto& rendererData = PerformanceStats::s_CurrentRendererData;
			ImGui::Separator();
			ImGui::Text("Draw Calls : %u", rendererData.DrawCallCount);
			ImGui::Text("Quad Count : %u", rendererData.QuadCount);
			ImGui::Text("Circle Count : %u", rendererData.CircleCount);
			ImGui::Text("Line Count : %u", rendererData.LineCount);
			ImGui::Text("Texture Count : %u", rendererData.TextureCount);
			ImGui::TreePop();
		}
		ImGui::Separator();

		ImGui::Text("%f FPS (%f ms/frame)", 1 / dt, dt * 1000);
		ImGui::End();
	}


	void ImGuiLayer::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();

		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}


	void ImGuiLayer::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
	
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	

	
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();

		ImGui_ImplGlfw_UpdateKeyModifiers(wnd);

		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 && e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), 1);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();

		ImGui_ImplGlfw_UpdateKeyModifiers(wnd);

		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 && e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), 0);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		//ImGui_ImplGlfw_Data* bd = ImGui_ImplGlfw_GetBackendData();
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();
		if (glfwGetInputMode(wnd, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			return false;

		ImGuiIO& io = ImGui::GetIO();
		double x = 0;
		double y = 0;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			int window_x, window_y;
			glfwGetWindowPos(wnd, &window_x, &window_y);
			x += window_x;
			y += window_y;
		}
		io.AddMousePosEvent((float)(e.GetX() + x), (float)(e.GetY() + y));
		//bd->LastValidMousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();


		ImGui_ImplGlfw_UpdateKeyModifiers(wnd);

			
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imgui_key = Key_RapierToImGui(e.GetKeyCode());
		io.AddKeyEvent(imgui_key, 1);
		//io.SetKeyEventNativeData(imgui_key, e.GetKeyCode(), e.GetScanCode()); // To support legacy indexing (<1.87 user code)

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		GLFWwindow* wnd = (GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow();


		ImGui_ImplGlfw_UpdateKeyModifiers(wnd);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imgui_key = Key_RapierToImGui(e.GetKeyCode());
		io.AddKeyEvent(imgui_key, 0);
		//io.SetKeyEventNativeData(imgui_key, e.GetKeyCode(), e.GetScanCode()); // To support legacy indexing (<1.87 user code)

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());


		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}