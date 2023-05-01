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


	////////////////////////////////////////////////////////////////////////////////////////
	/// Quads //////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

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


	static QuadVertex* l_QuadVertexBufferBasePtr = nullptr;
	static QuadVertex* l_QuadVertexBufferCurrentPtr = nullptr;

	static uint32_t l_CurrentQuadCount = 0;
	static Ref<VertexBuffer> l_QuadVertexBuffer = nullptr;



	////////////////////////////////////////////////////////////////////////////////////////
	/// Circles ////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


	struct CircleVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		int TexIndex;
		int EntityId;
		glm::vec2 LocalPosition;
		float MinimumRadius;
	};



	static constexpr uint32_t l_MaxCircleCount = 10000;
	static constexpr uint32_t l_MaxCircleVertices = 4 * l_MaxCircleCount;
	static constexpr uint32_t l_MaxCircleIndices = 6 * l_MaxCircleCount;


	static CircleVertex* l_CircleVertexBufferBasePtr = nullptr;
	static CircleVertex* l_CircleVertexBufferCurrentPtr = nullptr;

	static uint32_t l_CurrentCircleCount = 0;
	static Ref<VertexBuffer> l_CircleVertexBuffer = nullptr;




	////////////////////////////////////////////////////////////////////////////////////////
	/// Lines //////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


	struct LineVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		int EntityId;
	};



	static constexpr uint32_t l_MaxLineCount = 10000;
	static constexpr uint32_t l_MaxLineVertices = 2 * l_MaxLineCount;
	static constexpr uint32_t l_MaxLineIndices = 2 * l_MaxLineCount;


	static LineVertex* l_LineVertexBufferBasePtr = nullptr;
	static LineVertex* l_LineVertexBufferCurrentPtr = nullptr;

	static uint32_t l_CurrentLineCount = 0;
	static Ref<VertexBuffer> l_LineVertexBuffer = nullptr;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	static constexpr uint32_t l_MaxTextureCount = 32;

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
		RenderCommand::SetLineWidth(5.0f);
		CreateVertexArrays();
	}
	
	void Renderer2D::Shutdown() {
		delete[] l_QuadVertexBufferBasePtr;
	}

	void Renderer2D::BeginScene(const glm::mat4& camera) {
		RAPIER_CORE_ASSERT(!l_StartedScene2D, "Scene has already started!");

		l_StartedScene2D = true;
		l_SceneData2D.reset(new SceneData(camera));

		Ref<Shader> shaderQ = AssetManager::GetShader("Texture.rshader");
		shaderQ->Bind();
		shaderQ->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);


		Ref<Shader> shaderC = AssetManager::GetShader("Circle.rshader");
		shaderC->Bind();
		shaderC->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		

		Ref<Shader> shaderL = AssetManager::GetShader("Line.rshader");
		shaderL->Bind();
		shaderL->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);


		l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		l_CircleVertexBufferCurrentPtr = l_CircleVertexBufferCurrentPtr;
		l_LineVertexBufferCurrentPtr = l_LineVertexBufferCurrentPtr;
	}

	void Renderer2D::EndScene() {
		Renderer2D::Flush();
		l_StartedScene2D = false;
	}

	void Renderer2D::BeginEditorRender(const glm::mat4& camera) {
		RAPIER_CORE_ASSERT(!l_StartedScene2D, "Scene has already started!");

		l_StartedScene2D = true;
		l_SceneData2D.reset(new SceneData(camera));

		Ref<Shader> shaderQ = AssetManager::GetShader("Texture.rshader");
		shaderQ->Bind();
		shaderQ->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);


		Ref<Shader> shaderC = AssetManager::GetShader("Circle.rshader");
		shaderC->Bind();
		shaderC->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);


		Ref<Shader> shaderL = AssetManager::GetShader("Line.rshader");
		shaderL->Bind();
		shaderL->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);


		l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		l_CircleVertexBufferCurrentPtr = l_CircleVertexBufferCurrentPtr;
		l_LineVertexBufferCurrentPtr = l_LineVertexBufferCurrentPtr;
	}

	void Renderer2D::EndEditorRender() {
		Renderer2D::Flush();
		l_StartedScene2D = false;
	}



	void Renderer2D::Flush() {
		int samplers[l_MaxTextureCount];
		for (uint32_t i = 0; i < l_CurrentTextureCount; i++) {
			l_TextureSlots[i]->Bind(i);
			samplers[i] = i;
		}

		if (l_QuadVertexBufferCurrentPtr != l_QuadVertexBufferBasePtr)
		{
			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)l_QuadVertexBufferCurrentPtr - (uint8_t*)l_QuadVertexBufferBasePtr);
			l_QuadVertexBuffer->SetData(l_QuadVertexBufferBasePtr, dataSize);


			Ref<Shader> shader = AssetManager::GetShader("Texture.rshader");
			shader->Bind();
			shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawIndexed(l_VertexArrays["Texture"], l_CurrentQuadCount * 6);

			l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;
		
			l_CurrentQuadCount = 0;
		}

		if (l_CircleVertexBufferCurrentPtr != l_CircleVertexBufferBasePtr)
		{

			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)l_CircleVertexBufferCurrentPtr - (uint8_t*)l_CircleVertexBufferBasePtr);
			l_CircleVertexBuffer->SetData(l_CircleVertexBufferBasePtr, dataSize);

			Ref<Shader> shader = AssetManager::GetShader("Circle.rshader");
			shader->Bind();
			shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawIndexed(l_VertexArrays["Circle"], l_CurrentCircleCount * 6);

			l_CircleVertexBufferCurrentPtr = l_CircleVertexBufferBasePtr;
			l_CurrentCircleCount = 0;
		}

		if (l_LineVertexBufferCurrentPtr != l_LineVertexBufferBasePtr)
		{
			PerformanceStats::s_CurrentRendererData.DrawCallCount++;

			uint32_t dataSize = (uint32_t)((uint8_t*)l_LineVertexBufferCurrentPtr - (uint8_t*)l_LineVertexBufferBasePtr);
			l_LineVertexBuffer->SetData(l_LineVertexBufferBasePtr, dataSize);


			Ref<Shader> shader = AssetManager::GetShader("Line.rshader");
			shader->Bind();
			shader->UploadUniformIntArray("u_Texture", samplers, l_CurrentTextureCount);
			RenderCommand::DrawLines(l_VertexArrays["Line"], l_CurrentLineCount * 2);

			l_LineVertexBufferCurrentPtr = l_LineVertexBufferBasePtr;

			l_CurrentLineCount = 0;
		}


		for (uint32_t i = 1; i < l_MaxTextureCount; i++) {
			l_TextureSlots[i] = nullptr;
		}
		l_CurrentTextureCount = 1;
	}

	void Renderer2D::DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& color, int entityId) {
		PerformanceStats::s_CurrentRendererData.QuadCount++;

		bool isWhiteTexture;
		if (!texture) {
			texture = AssetManager::GetWhiteTexture();
			isWhiteTexture = true;
		}
		else {
			isWhiteTexture = texture == AssetManager::GetWhiteTexture();
		}

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

		if (textureSlot == 0 && !isWhiteTexture) {
			if (l_CurrentTextureCount >= l_MaxTextureCount) 
				Flush();

			PerformanceStats::s_CurrentRendererData.TextureCount++;
			
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




	void Renderer2D::DrawTexture(const glm::vec3& position, float rotation, const glm::vec2& size, 
		Ref<Texture2D> texture, const glm::vec4& color, int entityId) 
	{

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawTexture(transform, texture, color, entityId);
	}






	void Renderer2D::DrawCircle(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& color, int entityId, float minimumRadius) {
		PerformanceStats::s_CurrentRendererData.CircleCount++;

		bool isWhiteTexture;
		if (!texture) {
			texture = AssetManager::GetWhiteTexture();
			isWhiteTexture = true;
		}
		else {
			isWhiteTexture = texture == AssetManager::GetWhiteTexture();
		}

		uint32_t textureSlot = 0;

		if (l_CurrentCircleCount == l_MaxCircleCount) {
			Flush();
		}

		for (uint32_t i = 0; i < l_MaxTextureCount; i++) {
			if (texture == l_TextureSlots[i]) {
				textureSlot = i;
				break;
			}
		}

		if (textureSlot == 0 && !isWhiteTexture) {
			if (l_CurrentTextureCount >= l_MaxTextureCount)
				Flush();

			PerformanceStats::s_CurrentRendererData.TextureCount++;

			l_TextureSlots[l_CurrentTextureCount] = texture;
			textureSlot = l_CurrentTextureCount;
			l_CurrentTextureCount++;

		}

		static glm::vec4 temp;
		for (uint32_t i = 0; i < 4; i++) {
			// Position.x is scaled according to texture aspect ratio
			temp = l_QuadVertexPosition[i];
			temp.x *= (float)texture->GetWidth() / (float)texture->GetHeight();


			l_CircleVertexBufferCurrentPtr->Position = transform * temp;
			l_CircleVertexBufferCurrentPtr->Color = color;
			l_CircleVertexBufferCurrentPtr->TexCoords = l_TextureCoords[i];
			l_CircleVertexBufferCurrentPtr->TexIndex = textureSlot;
			l_CircleVertexBufferCurrentPtr->EntityId = entityId;
			l_CircleVertexBufferCurrentPtr->LocalPosition = l_QuadVertexPosition[i] * 2.0f;
			l_CircleVertexBufferCurrentPtr->MinimumRadius = minimumRadius;
			l_CircleVertexBufferCurrentPtr++;
		}

		l_CurrentCircleCount++;
	}

	void Renderer2D::DrawCircle(const glm::vec3& position, const glm::vec2& size,
		Ref<Texture2D> texture, const glm::vec4& color, int entityId, float minimumRadius) 
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawCircle(transform, texture, color, entityId, minimumRadius);
	}


	void Renderer2D::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityId) {
		if (l_CurrentLineCount == l_MaxLineCount) {
			Flush();
		}
		PerformanceStats::s_CurrentRendererData.LineCount++;


		l_LineVertexBufferCurrentPtr->Position = p0;
		l_LineVertexBufferCurrentPtr->Color = color;
		l_LineVertexBufferCurrentPtr->EntityId = entityId;
		l_LineVertexBufferCurrentPtr++;

		l_LineVertexBufferCurrentPtr->Position = p1;
		l_LineVertexBufferCurrentPtr->Color = color;
		l_LineVertexBufferCurrentPtr->EntityId = entityId;
		l_LineVertexBufferCurrentPtr++;

		l_CurrentLineCount++;


	}



	void Renderer2D::CreateVertexArrays() {

		Ref<IndexBuffer> ib;

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

		ib = IndexBuffer::Create(QuadIndices, l_MaxQuadIndices);
		delete[] QuadIndices;

		{

			Ref<VertexArray> va = VertexArray::Create();

			l_QuadVertexBuffer = VertexBuffer::Create(l_MaxQuadVertices * sizeof(QuadVertex));
			l_QuadVertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Float2, "a_TextureCoord"},
				{ShaderDataType::Int, "a_TextureIndex"},
				{ShaderDataType::Int, "a_EntityId"},
				});

			va->AddVertexBuffer(l_QuadVertexBuffer);

			l_QuadVertexBufferBasePtr = new QuadVertex[l_MaxQuadVertices];
			l_QuadVertexBufferCurrentPtr = l_QuadVertexBufferBasePtr;

			va->SetIndexBuffer(ib);

			l_VertexArrays.insert({ "Texture", va });

		}


		{

			Ref<VertexArray> va = VertexArray::Create();

			l_CircleVertexBuffer = VertexBuffer::Create(l_MaxCircleVertices * sizeof(CircleVertex));
			l_CircleVertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Float2, "a_TextureCoord"},
				{ShaderDataType::Int, "a_TextureIndex"},
				{ShaderDataType::Int, "a_EntityId"},
				{ShaderDataType::Float2, "a_LocalPosition"},
				{ShaderDataType::Float, "a_MinimumRadius"},
				});

			va->AddVertexBuffer(l_CircleVertexBuffer);

			l_CircleVertexBufferBasePtr = new CircleVertex[l_MaxCircleVertices];
			l_CircleVertexBufferCurrentPtr = l_CircleVertexBufferBasePtr;

			va->SetIndexBuffer(ib);

			l_VertexArrays.insert({ "Circle", va });

		}

		{

			Ref<VertexArray> va = VertexArray::Create();

			l_LineVertexBuffer = VertexBuffer::Create(l_MaxLineVertices * sizeof(LineVertex));
			l_LineVertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Int, "a_EntityId"},
				});

			va->AddVertexBuffer(l_LineVertexBuffer);

			l_LineVertexBufferBasePtr = new LineVertex[l_MaxLineVertices];
			l_LineVertexBufferCurrentPtr = l_LineVertexBufferBasePtr;

			l_VertexArrays.insert({ "Line", va });

		}

		l_TextureSlots.resize(l_MaxTextureCount);
		l_TextureSlots[0] = AssetManager::GetWhiteTexture();
	}

}