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

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));


		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.75f, 0.0f,
			 0.5f,  0.75f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.75f,  0.0f, 0.0f
		};

		uint32_t indices[] = { 0, 1, 4, 4, 2, 3, 3, 0, 4 };


		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::shared_ptr<std::string> vertexShader = FileSystem::GetData("../Irene/res/Shader/VertexShader.ishader", FileType::Shader);
		std::shared_ptr<std::string> fragmentShader = FileSystem::GetData("../Irene/res/Shader/FragmentShader.ishader", FileType::Shader);
		
		m_Shader.reset(new OpenGLShader(*vertexShader, *fragmentShader));

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

	void Application::Run() {

		while (m_Running) {

			RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

