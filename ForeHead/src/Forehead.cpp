#include "Rapier.h"
#include "RapierEntryPoint.h"

#include "Forehead.h"
#include "ForeheadLayer.h"
#include "Geometry/Pentagon.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Forehead {


	glm::vec2 Forehead::s_CameraVelocity = { 0, 0 };
	float Forehead::s_CameraRotationVelocity = 0;

	Forehead::Forehead() {

		using namespace Rapier;

		PushLayer(new ForeheadLayer());


		m_VertexArray = VertexArray::Create();
		m_VertexArray->Bind();

		float vertices[] = {
			-0.5, -0.5, 0.0, 0.0, 0.0,
			 0.5, -0.5, 0.0, 1.0, 0.0,
			 0.5,  0.5, 0.0, 1.0, 1.0,
			-0.5,  0.5, 0.0, 0.0, 1.0
		};

		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0
		};

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TextureCoord" }
		};



		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_Shader = Shader::Create("../Forehead/res/Shader/TextureVertex.rshader", "../Forehead/res/Shader/TextureFragment.rshader");

		m_Texture = Texture2D::Create("../Forehead/res/Texture/irene-gyatekora.png");
		
		m_Shader->Bind();
		m_Shader->UploadUniformInt("u_Texture", 0);



		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });


	}

	Forehead::~Forehead() {

	}

	void Forehead::OnUpdate(Rapier::DeltaTime dt) {

		using namespace Rapier;

		RenderCommand::Clear();

		OrthographicCamera& cam = OrthographicCamera::GetCamera();


		Renderer::BeginScene(cam);

		m_Texture->Bind();
		Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		Renderer::EndScene();
	}


}

Rapier::Application* Rapier::CreateApplication() {
	return new Forehead::Forehead();
}