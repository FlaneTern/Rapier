#pragma once
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

#include "Renderer/VertexArray.h"

#include "Time/DeltaTime.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace IRENE {

	class IRENE_API Application
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


	//private: //temporarily protected
	protected:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;


		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		std::chrono::high_resolution_clock::time_point m_PrevTime = std::chrono::high_resolution_clock::now();
	};

	Application* CreateApplication();
}

	