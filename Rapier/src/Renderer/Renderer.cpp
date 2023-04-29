#include "ipch.h"
#include "Renderer.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "PerformanceStats.h"


#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	static Scope<SceneData> l_SceneData;
	static bool l_StartedScene = false;

	

	void Renderer::EndScene() {
		l_StartedScene = false;
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		int TexIndex;
		int EntityId;
	};



	static constexpr uint32_t l_MaxQuadCount = 10000;
	static constexpr uint32_t l_MaxQuadVertices = 4 * l_MaxQuadCount;
	static constexpr uint32_t l_MaxQuadIndices = 6 * l_MaxQuadCount;
	static constexpr uint32_t l_MaxTextureCount = 32;


	static QuadVertex* l_QuadVertexBufferBasePtr = nullptr;
	static QuadVertex* l_QuadVertexBufferCurrentPtr = nullptr;

	static uint32_t l_CurrentQuadCount = 0;
	static Ref<VertexBuffer> l_QuadVertexBuffer = nullptr;



	static constexpr glm::vec4 l_QuadVertexPosition[] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f, },
		{  0.5f, -0.5f, 0.0f, 1.0f, },
		{  0.5f,  0.5f, 0.0f, 1.0f, },
		{ -0.5f,  0.5f, 0.0f, 1.0f  }
	};

	static constexpr glm::vec2 l_TextureCoords[] = {
		{ 0.0f, 0.0f, },
		{ 1.0f, 0.0f, },
		{ 1.0f, 1.0f, },
		{ 0.0f, 1.0f  }
	};


	static uint32_t l_CurrentTextureCount = 1;
	static std::vector<Ref<Texture2D>> l_TextureSlots;


	static Scope<SceneData> l_SceneData2D = nullptr;
	bool l_StartedScene2D = false;
	static std::unordered_map<std::string, Ref<VertexArray>> l_VertexArrays;


	void Renderer2D::Init() {
		RenderCommand::Init();
		CreateVertexArrays();
	}
	
	void Renderer2D::Shutdown() {
		delete[] l_QuadVertexBufferBasePtr;
	}

	void Renderer2D::BeginScene(const glm::mat4& camera) {
		RAPIER_CORE_ASSERT(!l_StartedScene2D, "Scene has already started!");

		l_StartedScene2D = true;
		l_SceneData2D.reset(new SceneData(camera));

		Ref<Shader> shader = AssetManager::GetShader("Texture.rshader");
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);

		l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		
	}

	void Renderer2D::EndScene() {
		Renderer2D::Flush();
		l_StartedScene2D = false;
	}



	void Renderer2D::Flush() {
		PerformanceStats::AddDrawCallCount();

		uint32_t dataSize = (uint32_t)((uint8_t*)l_QuadVertexBufferCurrentPtr - (uint8_t*)l_QuadVertexBufferBasePtr);
		l_QuadVertexBuffer->SetData(l_QuadVertexBufferBasePtr, dataSize);

		// Bind textures
		int samplers[l_MaxTextureCount];
		for (uint32_t i = 0; i < l_CurrentTextureCount; i++) {
			l_TextureSlots[i]->Bind(i);
			samplers[i] = i;
		}


		Ref<Shader> shader = AssetManager::GetShader("Texture.rshader");
		shader->Bind();
		shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
		RenderCommand::DrawIndexed(l_VertexArrays["Texture"], l_CurrentQuadCount * 6);

		l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		
		for (uint32_t i = 1; i < l_MaxTextureCount; i++) {
			l_TextureSlots[i] = nullptr;
		}
		l_CurrentTextureCount = 1;
		l_CurrentQuadCount = 0;
	}

	void Renderer2D::DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& color, int entityId) {
		PerformanceStats::AddQuadCount();

		Ref<Shader> shader = AssetManager::GetShader("Texture.rshader");

		uint32_t textureSlot = 0;

		if (l_CurrentQuadCount == l_MaxQuadCount) {
			Flush();
		}

		for (uint32_t i = 0; i < l_MaxTextureCount; i++) {
			if (texture == l_TextureSlots[i]) {
				textureSlot = i;
				break;
			}
		}

		bool isWhiteTexture = texture == AssetManager::GetWhiteTexture();
		if (textureSlot == 0 && !isWhiteTexture) {
			if (l_CurrentTextureCount >= l_MaxTextureCount) 
				Flush();

			PerformanceStats::AddTextureCount();
			
			l_TextureSlots[l_CurrentTextureCount] = texture;
			textureSlot = l_CurrentTextureCount;
			l_CurrentTextureCount++;
			

		}

		static glm::vec4 temp;
		for (uint32_t i = 0; i < 4; i++) {
			// Position.x is scaled according to texture aspect ratio
			temp = l_QuadVertexPosition[i];
			temp.x *= (float)texture->GetWidth() / (float)texture->GetHeight();


			l_QuadVertexBufferCurrentPtr->Position = transform * temp;
			l_QuadVertexBufferCurrentPtr->Color = color;
			l_QuadVertexBufferCurrentPtr->TexCoords = l_TextureCoords[i];
			l_QuadVertexBufferCurrentPtr->TexIndex = textureSlot;
			l_QuadVertexBufferCurrentPtr->EntityId = entityId;
			l_QuadVertexBufferCurrentPtr++;
		}

		l_CurrentQuadCount++;
	}

	void Renderer2D::DrawTexture(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float rotation, const glm::vec4& color, int entityId) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawTexture(transform, texture, color, entityId);
	}


	void Renderer2D::CreateVertexArrays() {
		Ref<VertexArray> va = VertexArray::Create();

		l_QuadVertexBuffer = VertexBuffer::Create(l_MaxQuadVertices * sizeof(QuadVertex));
		l_QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TextureCoord"},
			{ShaderDataType::Float, "a_TextureIndex"},
			{ShaderDataType::Int, "a_EntityId"},
			});

		va->AddVertexBuffer(l_QuadVertexBuffer);

		l_QuadVertexBufferBasePtr = new QuadVertex[l_MaxQuadVertices];
		l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		uint32_t* QuadIndices = new uint32_t[l_MaxQuadIndices];

		uint32_t offset = 0;
		for (int i = 0; i < l_MaxQuadIndices; i += 6) {
			QuadIndices[i + 0] = offset + 0;
			QuadIndices[i + 1] = offset + 1;
			QuadIndices[i + 2] = offset + 2;
			QuadIndices[i + 3] = offset + 2;
			QuadIndices[i + 4] = offset + 3;
			QuadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> ib = IndexBuffer::Create(QuadIndices, l_MaxQuadIndices);

		va->SetIndexBuffer(ib);

		delete[] QuadIndices;
		l_VertexArrays.insert({ "Texture", va });


		l_TextureSlots.resize(l_MaxTextureCount);
		l_TextureSlots[0] = AssetManager::GetWhiteTexture();

	}

	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color) {
		Ref<Shader> shader = AssetManager::GetShader("Circle.rshader");
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat4("u_Color", color);


		Ref<VertexArray> va = l_VertexArrays["Quad"];
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

	void Renderer2D::DrawCircle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		DrawCircle(transform, color);
	}

#if 0
	void Renderer2D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
#endif
}