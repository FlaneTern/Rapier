#include "ipch.h"


#include "Application.h"
#include "Input.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Renderer.h"

#include "FileSystem/FileSystem.h"


namespace IRENE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		IRENE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		Renderer::Create();

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));


		PushOverlay(new ImGuiLayer);

	}	



	Application::~Application() {

	}


	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::OnUpdate(DeltaTime dt) {
		IRENE_CORE_ASSERT(false, "OnUpdate (MainLoop) hasn't been set!");
	}


	void Application::Run() {

		while (m_Running) {
			DeltaTime dt = DeltaTime(m_PrevTime);
			m_PrevTime = std::chrono::high_resolution_clock::now();
			//IRENE_CORE_INFO("time : {0} seconds, {1} fps", dt, 1 / dt);
			OnUpdate(dt);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(dt);
			}

			m_Window->OnUpdate();
		}
	}




	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

