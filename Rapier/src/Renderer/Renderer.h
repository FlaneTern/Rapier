#pragma once

#include "Renderer/RenderCommand.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Assets/AssetManager.h"


namespace Rapier {

	struct SceneData {
		SceneData(const glm::mat4& camera) : ViewProjectionMatrix(camera) {}
		glm::mat4 ViewProjectionMatrix;
	};


	class Renderer {
	public:
		static void BeginScene(const glm::mat4& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		Renderer() = delete;

	};



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	class Renderer2D {
	public:
		static void BeginScene(const glm::mat4& camera);
		static void EndScene();


		static void BeginEditorRender(const glm::mat4& camera);
		static void EndEditorRender();



		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void DrawTexture(const glm::mat4& transform,
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1);
		static void DrawTexture(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, float rotation = 0.0f, const glm::vec2& size = { 1.0f, 1.0f },
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1);

		static void DrawCircle(const glm::mat4& transform,
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1, float minimumRadius = 0.0f);
		static void DrawCircle(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec2& size = { 1.0f, 1.0f },
			Ref<Texture2D> texture = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1, float minimumRadius = 0.0f);


		static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityId = -1);


		static void Init();
		static void Shutdown();

		static void Flush();

	private:
		static void CreateVertexArrays();
		Renderer2D() = delete;

	};

}