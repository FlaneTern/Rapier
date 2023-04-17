#include "Rapier.h"
#include "RapierEntryPoint.h"

#include "Forehead.h"
#include "ForeheadLayer.h"
#include "Geometry/Pentagon.h"

namespace Forehead {


	glm::vec2 Forehead::s_CameraVelocity = { 0, 0 };
	float Forehead::s_CameraRotationVelocity = 0;

	Forehead::Forehead() {

		using namespace Rapier;

		PushLayer(new ForeheadLayer());


		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(Pentagon::s_Pentagon->GetVertices(), Pentagon::s_Pentagon->GetVerticesSize()));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(Pentagon::s_Pentagon->GetIndices(), Pentagon::s_Pentagon->GetIndicesSize() / sizeof(int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::shared_ptr<std::string> vertexShader = FileSystem::GetData("../Rapier/res/Shader/VertexShader.ishader", FileType::Shader);
		std::shared_ptr<std::string> fragmentShader = FileSystem::GetData("../Rapier/res/Shader/FragmentShader.ishader", FileType::Shader);

		m_Shader.reset(Shader::Create(*vertexShader, *fragmentShader));

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });


	}

	Forehead::~Forehead() {

	}

	void Forehead::OnUpdate(Rapier::DeltaTime dt) {

		using namespace Rapier;

	
		RenderCommand::Clear();


		OrthographicCamera& cam = OrthographicCamera::GetCamera();

		Renderer::BeginScene(cam);


		Renderer::Submit(m_VertexArray, m_Shader);

		Renderer::EndScene();
	}


}

Rapier::Application* Rapier::CreateApplication() {
	return new Forehead::Forehead();
}