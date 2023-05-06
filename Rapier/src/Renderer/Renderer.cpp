#include "ipch.h"
#include "Renderer/Renderer.h"
#include "Renderer/SceneRenderer.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "PerformanceStats.h"


#include "glm/gtc/matrix_transform.hpp"

namespace Rapier
{

	Renderer2D::Renderer2D() 
	{
		Init();
	}

	Renderer2D::~Renderer2D()
	{
		Shutdown();
	}

	static constexpr uint32_t l_MaxTextureCount = 32;

	static constexpr glm::vec4 l_QuadVertexPosition[] = 
	{
		{ -0.5f, -0.5f, 0.0f, 1.0f, },
		{  0.5f, -0.5f, 0.0f, 1.0f, },
		{  0.5f,  0.5f, 0.0f, 1.0f, },
		{ -0.5f,  0.5f, 0.0f, 1.0f  }
	};

	static constexpr glm::vec2 l_TextureCoords[] =
	{
		{ 0.0f, 0.0f, },
		{ 1.0f, 0.0f, },
		{ 1.0f, 1.0f, },
		{ 0.0f, 1.0f  }
	};


	static uint32_t l_CurrentTextureCount = 1;
	static std::vector<Ref<Texture2D>> l_TextureSlots;


	void Renderer2D::Init() 
	{
		RenderCommand::Init();
		RenderCommand::SetLineWidth(5.0f);
		CreateVertexArrays();

		m_QuadBuffer.Shader = AssetManager::GetShader("Texture.rshader");
		m_CircleBuffer.Shader = AssetManager::GetShader("Circle.rshader");
		m_LineBuffer.Shader = AssetManager::GetShader("Line.rshader");
	}
	
	void Renderer2D::Shutdown() 
	{
		delete[] m_QuadBuffer.VertexBufferBasePtr;
		delete[] m_CircleBuffer.VertexBufferBasePtr;
		delete[] m_LineBuffer.VertexBufferBasePtr;
	}

	void Renderer2D::BeginScene()
	{

		auto sceneData = m_SceneData.lock();

		m_QuadBuffer.Shader->Bind();
		m_QuadBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);

		m_CircleBuffer.Shader->Bind();
		m_CircleBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);
		
		m_LineBuffer.Shader->Bind();
		m_LineBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);


		m_QuadBuffer.VertexBufferCurrentPtr = m_QuadBuffer.VertexBufferBasePtr;
		m_LineBuffer.VertexBufferCurrentPtr = m_LineBuffer.VertexBufferBasePtr;
		m_CircleBuffer.VertexBufferCurrentPtr = m_CircleBuffer.VertexBufferBasePtr;
	}

	void Renderer2D::EndScene()
	{
		Renderer2D::Flush();
	}


	void Renderer2D::DebugFlush(Ref<SceneData> data)
	{
		// TODO: Implement resolver if debug renderer buffer is full /////////////

		DepthFunction prevDepthFunction = RenderCommand::GetDepthFunction();
		RenderCommand::SetDepthFunction(DepthFunction::Always);
		SetSceneData(data);
		
		auto sceneData = m_SceneData.lock();

		m_QuadBuffer.Shader->Bind();
		m_QuadBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);

		m_CircleBuffer.Shader->Bind();
		m_CircleBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);

		m_LineBuffer.Shader->Bind();
		m_LineBuffer.Shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);

		Renderer2D::Flush();
		
		RenderCommand::SetDepthFunction(prevDepthFunction);
	}

	void Renderer2D::Flush()
	{
		int samplers[l_MaxTextureCount];
		for (uint32_t i = 0; i < l_CurrentTextureCount; i++)
		{
			l_TextureSlots[i]->Bind(i);
			samplers[i] = i;
		}

		if (m_QuadBuffer.VertexBufferCurrentPtr != m_QuadBuffer.VertexBufferBasePtr)
		{
			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadBuffer.VertexBufferCurrentPtr - (uint8_t*)m_QuadBuffer.VertexBufferBasePtr);
			m_QuadBuffer.VertexBuffer->SetData(m_QuadBuffer.VertexBufferBasePtr, dataSize);

			m_QuadBuffer.Shader->Bind();
			m_QuadBuffer.Shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawIndexed(m_QuadBuffer.VertexArray, m_QuadBuffer.CurrentQuadCount * 6);

			m_QuadBuffer.VertexBufferCurrentPtr = m_QuadBuffer.VertexBufferBasePtr;
		
			m_QuadBuffer.CurrentQuadCount = 0;
		}

		if (m_CircleBuffer.VertexBufferCurrentPtr != m_CircleBuffer.VertexBufferBasePtr)
		{

			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)m_CircleBuffer.VertexBufferCurrentPtr - (uint8_t*)m_CircleBuffer.VertexBufferBasePtr);
			m_CircleBuffer.VertexBuffer->SetData(m_CircleBuffer.VertexBufferBasePtr, dataSize);

			m_CircleBuffer.Shader->Bind();
			m_CircleBuffer.Shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawIndexed(m_CircleBuffer.VertexArray, m_CircleBuffer.CurrentCircleCount * 6);

			m_CircleBuffer.VertexBufferCurrentPtr = m_CircleBuffer.VertexBufferBasePtr;
			m_CircleBuffer.CurrentCircleCount = 0;
		}

		if (m_LineBuffer.VertexBufferCurrentPtr != m_LineBuffer.VertexBufferBasePtr)
		{
			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)m_LineBuffer.VertexBufferCurrentPtr - (uint8_t*)m_LineBuffer.VertexBufferBasePtr);
			m_LineBuffer.VertexBuffer->SetData(m_LineBuffer.VertexBufferBasePtr, dataSize);

			m_LineBuffer.Shader->Bind();
			m_LineBuffer.Shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawLines(m_LineBuffer.VertexArray, m_LineBuffer.CurrentLineCount * 2);

			m_LineBuffer.VertexBufferCurrentPtr = m_LineBuffer.VertexBufferBasePtr;

			m_LineBuffer.CurrentLineCount = 0;
		}


		for (uint32_t i = 1; i < l_MaxTextureCount; i++) 
		{
			l_TextureSlots[i] = nullptr;
		}
		l_CurrentTextureCount = 1;
	}

	void Renderer2D::DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& color, int entityId) 
	{
		PerformanceStats::s_CurrentRendererData.QuadCount++;

		bool isWhiteTexture;
		if (!texture) 
		{
			texture = AssetManager::GetWhiteTexture();
			isWhiteTexture = true;
		}
		else 
		{
			isWhiteTexture = texture == AssetManager::GetWhiteTexture();
		}

		uint32_t textureSlot = 0;

		if (m_QuadBuffer.CurrentQuadCount == m_QuadBuffer.c_MaxQuadCount)
		{
			Flush();
		}

		for (uint32_t i = 0; i < l_MaxTextureCount; i++)
		{
			if (texture == l_TextureSlots[i]) 
			{
				textureSlot = i;
				break;
			}
		}

		if (textureSlot == 0 && !isWhiteTexture) 
		{
			if (l_CurrentTextureCount >= l_MaxTextureCount) 
				Flush();

			PerformanceStats::s_CurrentRendererData.TextureCount++;
			
			l_TextureSlots[l_CurrentTextureCount] = texture;
			textureSlot = l_CurrentTextureCount;
			l_CurrentTextureCount++;
			

		}

		static glm::vec4 temp;
		for (uint32_t i = 0; i < 4; i++) 
		{
			// Position.x is scaled according to texture aspect ratio
			temp = l_QuadVertexPosition[i];
			temp.x *= (float)texture->GetWidth() / (float)texture->GetHeight();

			m_QuadBuffer.VertexBufferCurrentPtr->Position = transform * temp;
			m_QuadBuffer.VertexBufferCurrentPtr->Color = color;
			m_QuadBuffer.VertexBufferCurrentPtr->TexCoords = l_TextureCoords[i];
			m_QuadBuffer.VertexBufferCurrentPtr->TexIndex = textureSlot;
			m_QuadBuffer.VertexBufferCurrentPtr->EntityId = entityId;
			m_QuadBuffer.VertexBufferCurrentPtr++;
		}

		m_QuadBuffer.CurrentQuadCount++;
	}




	void Renderer2D::DrawTexture(const glm::vec3& position, float rotation, const glm::vec2& size, 
		Ref<Texture2D> texture, const glm::vec4& color, int entityId) 
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawTexture(transform, texture, color, entityId);
	}






	void Renderer2D::DrawCircle(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& color, int entityId, float minimumRadius) 
	{
		PerformanceStats::s_CurrentRendererData.CircleCount++;

		bool isWhiteTexture;
		if (!texture)
		{
			texture = AssetManager::GetWhiteTexture();
			isWhiteTexture = true;
		}
		else
		{
			isWhiteTexture = texture == AssetManager::GetWhiteTexture();
		}

		uint32_t textureSlot = 0;

		if (m_CircleBuffer.CurrentCircleCount == m_CircleBuffer.c_MaxCircleCount)
		{
			Flush();
		}

		for (uint32_t i = 0; i < l_MaxTextureCount; i++) 
		{
			if (texture == l_TextureSlots[i])
			{
				textureSlot = i;
				break;
			}
		}

		if (textureSlot == 0 && !isWhiteTexture) 
		{
			if (l_CurrentTextureCount >= l_MaxTextureCount)
				Flush();

			PerformanceStats::s_CurrentRendererData.TextureCount++;

			l_TextureSlots[l_CurrentTextureCount] = texture;
			textureSlot = l_CurrentTextureCount;
			l_CurrentTextureCount++;

		}

		static glm::vec4 temp;
		for (uint32_t i = 0; i < 4; i++)
		{
			// Position.x is scaled according to texture aspect ratio
			temp = l_QuadVertexPosition[i];
			temp.x *= (float)texture->GetWidth() / (float)texture->GetHeight();


			m_CircleBuffer.VertexBufferCurrentPtr->Position = transform * temp;
			m_CircleBuffer.VertexBufferCurrentPtr->Color = color;
			m_CircleBuffer.VertexBufferCurrentPtr->TexCoords = l_TextureCoords[i];
			m_CircleBuffer.VertexBufferCurrentPtr->TexIndex = textureSlot;
			m_CircleBuffer.VertexBufferCurrentPtr->EntityId = entityId;
			m_CircleBuffer.VertexBufferCurrentPtr->LocalPosition = l_QuadVertexPosition[i] * 2.0f;
			m_CircleBuffer.VertexBufferCurrentPtr->MinimumRadius = minimumRadius;
			m_CircleBuffer.VertexBufferCurrentPtr++;
		}

		m_CircleBuffer.CurrentCircleCount++;
	}

	void Renderer2D::DrawCircle(const glm::vec3& position, const glm::vec2& size,
		Ref<Texture2D> texture, const glm::vec4& color, int entityId, float minimumRadius) 
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawCircle(transform, texture, color, entityId, minimumRadius);
	}


	void Renderer2D::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityId) 
	{
		if (m_LineBuffer.CurrentLineCount == m_LineBuffer.c_MaxLineCount) 
		{
			Flush();
		}
		PerformanceStats::s_CurrentRendererData.LineCount++;


		m_LineBuffer.VertexBufferCurrentPtr->Position = p0;
		m_LineBuffer.VertexBufferCurrentPtr->Color = color;
		m_LineBuffer.VertexBufferCurrentPtr->EntityId = entityId;
		m_LineBuffer.VertexBufferCurrentPtr++;
					
		m_LineBuffer.VertexBufferCurrentPtr->Position = p1;
		m_LineBuffer.VertexBufferCurrentPtr->Color = color;
		m_LineBuffer.VertexBufferCurrentPtr->EntityId = entityId;
		m_LineBuffer.VertexBufferCurrentPtr++;

		m_LineBuffer.CurrentLineCount++;


	}



	void Renderer2D::CreateVertexArrays() 
	{

		Ref<IndexBuffer> ib;

		uint32_t* QuadIndices = new uint32_t[m_QuadBuffer.c_MaxQuadIndices];

		uint32_t offset = 0;
		for (int i = 0; i < m_QuadBuffer.c_MaxQuadIndices; i += 6)
		{
			QuadIndices[i + 0] = offset + 0;
			QuadIndices[i + 1] = offset + 1;
			QuadIndices[i + 2] = offset + 2;
			QuadIndices[i + 3] = offset + 2;
			QuadIndices[i + 4] = offset + 3;
			QuadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		ib = IndexBuffer::Create(QuadIndices, m_QuadBuffer.c_MaxQuadIndices);
		delete[] QuadIndices;

		{

			m_QuadBuffer.VertexArray = VertexArray::Create();

			m_QuadBuffer.VertexBuffer = VertexBuffer::Create(m_QuadBuffer.c_MaxQuadVertices * sizeof(QuadVertex));
			m_QuadBuffer.VertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Float2, "a_TextureCoord"},
				{ShaderDataType::Int, "a_TextureIndex"},
				{ShaderDataType::Int, "a_EntityId"},
				});

			m_QuadBuffer.VertexArray->AddVertexBuffer(m_QuadBuffer.VertexBuffer);

			m_QuadBuffer.VertexBufferBasePtr = new QuadVertex[m_QuadBuffer.c_MaxQuadVertices];
			m_QuadBuffer.VertexBufferCurrentPtr = m_QuadBuffer.VertexBufferBasePtr;

			m_QuadBuffer.VertexArray->SetIndexBuffer(ib);

		}


		{

			m_CircleBuffer.VertexArray = VertexArray::Create();

			m_CircleBuffer.VertexBuffer = VertexBuffer::Create(m_CircleBuffer.c_MaxCircleVertices * sizeof(CircleVertex));
			m_CircleBuffer.VertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Float2, "a_TextureCoord"},
				{ShaderDataType::Int, "a_TextureIndex"},
				{ShaderDataType::Int, "a_EntityId"},
				{ShaderDataType::Float2, "a_LocalPosition"},
				{ShaderDataType::Float, "a_MinimumRadius"},
				});

			m_CircleBuffer.VertexArray->AddVertexBuffer(m_CircleBuffer.VertexBuffer);

			m_CircleBuffer.VertexBufferBasePtr = new CircleVertex[m_CircleBuffer.c_MaxCircleVertices];
			m_CircleBuffer.VertexBufferCurrentPtr = m_CircleBuffer.VertexBufferBasePtr;

			m_CircleBuffer.VertexArray->SetIndexBuffer(ib);

		}

		{

			m_LineBuffer.VertexArray = VertexArray::Create();

			m_LineBuffer.VertexBuffer = VertexBuffer::Create(m_LineBuffer.c_MaxLineVertices * sizeof(LineVertex));
			m_LineBuffer.VertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Int, "a_EntityId"},
				});

			m_LineBuffer.VertexArray->AddVertexBuffer(m_LineBuffer.VertexBuffer);

			m_LineBuffer.VertexBufferBasePtr = new LineVertex[m_LineBuffer.c_MaxLineVertices];
			m_LineBuffer.VertexBufferCurrentPtr = m_LineBuffer.VertexBufferBasePtr;

		}

		l_TextureSlots.resize(l_MaxTextureCount);
		l_TextureSlots[0] = AssetManager::GetWhiteTexture();
	}

}