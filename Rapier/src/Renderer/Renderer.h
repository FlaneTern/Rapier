#pragma once

#include "Renderer/RenderCommand.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Assets/AssetManager.h"


namespace Rapier 
{

	struct SceneData;


	////////////////////////////////////////////////////////////////////////////////////////
	/// Quads //////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	struct QuadVertex 
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		int TexIndex;
		int EntityId;
	};

	struct Renderer2DQuadBuffer
	{
		static constexpr uint32_t c_MaxQuadCount = 10000;
		static constexpr uint32_t c_MaxQuadVertices = 4 * c_MaxQuadCount;
		static constexpr uint32_t c_MaxQuadIndices = 6 * c_MaxQuadCount;


		QuadVertex* VertexBufferBasePtr = nullptr;
		QuadVertex* VertexBufferCurrentPtr = nullptr;

		uint32_t CurrentQuadCount = 0;
		Ref<VertexBuffer> VertexBuffer = nullptr;
		Ref<VertexArray> VertexArray = nullptr;
		Ref<Shader> Shader = nullptr;
	};



	////////////////////////////////////////////////////////////////////////////////////////
	/// Circles ////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


	struct CircleVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		int TexIndex;
		int EntityId;
		glm::vec2 LocalPosition;
		float MinimumRadius;
	};


	struct Renderer2DCircleBuffer
	{

		static constexpr uint32_t c_MaxCircleCount = 10000;
		static constexpr uint32_t c_MaxCircleVertices = 4 * c_MaxCircleCount;
		static constexpr uint32_t c_MaxCircleIndices = 6 * c_MaxCircleCount;


		CircleVertex* VertexBufferBasePtr = nullptr;
		CircleVertex* VertexBufferCurrentPtr = nullptr;

		uint32_t CurrentCircleCount = 0;
		Ref<VertexBuffer> VertexBuffer = nullptr;
		Ref<VertexArray> VertexArray = nullptr;
		Ref<Shader> Shader = nullptr;
	};


	////////////////////////////////////////////////////////////////////////////////////////
	/// Lines //////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		int EntityId;
	};

	struct Renderer2DLineBuffer
	{

		static constexpr uint32_t c_MaxLineCount = 10000;
		static constexpr uint32_t c_MaxLineVertices = 2 * c_MaxLineCount;
		static constexpr uint32_t c_MaxLineIndices = 2 * c_MaxLineCount;


		LineVertex* VertexBufferBasePtr = nullptr;
		LineVertex* VertexBufferCurrentPtr = nullptr;

		uint32_t CurrentLineCount = 0;
		Ref<VertexBuffer> VertexBuffer = nullptr;
		Ref<VertexArray> VertexArray = nullptr;
		Ref<Shader> Shader = nullptr;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	class RAPIER_API Renderer2D 
	{
	public:
		Renderer2D();
		~Renderer2D();
		void BeginScene();
		void EndScene();

		void DrawTexture(const glm::mat4& transform,
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1);
		void DrawTexture(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, float rotation = 0.0f, const glm::vec2& size = { 1.0f, 1.0f },
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1);

		void DrawCircle(const glm::mat4& transform,
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1, float minimumRadius = 0.0f);
		void DrawCircle(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec2& size = { 1.0f, 1.0f },
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1, float minimumRadius = 0.0f);


		void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityId = -1);


		void Init();
		void Shutdown();

		void Flush();

		void SetSceneData(Ref<SceneData> data) { m_SceneData = data; }

	private:
		void CreateVertexArrays();

		Renderer2DQuadBuffer m_QuadBuffer;
		Renderer2DCircleBuffer m_CircleBuffer;
		Renderer2DLineBuffer m_LineBuffer;

		WeakRef<SceneData> m_SceneData;


#ifdef RAPIER_DEBUG
	public:
		void DebugFlush(Ref<SceneData> data);
#endif
	};


	typedef Renderer2D DebugRendererIMPL;
}