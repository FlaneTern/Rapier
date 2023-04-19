#pragma once
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Assets/Shader/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Assets/Texture/Texture.h"

#include "Camera/OrthographicCameraController.h"

#include "Time/DeltaTime.h"

#include "Assets/Shader/Shader.h"



namespace Rapier {

	class RAPIER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		virtual void OnUpdate(DeltaTime dt);
		virtual void PostUpdate();



		Ref<OrthographicCameraController> m_CameraController;


	protected:


	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		std::chrono::high_resolution_clock::time_point m_PrevTime = std::chrono::high_resolution_clock::now();
	};

	Application* CreateApplication();
}

	