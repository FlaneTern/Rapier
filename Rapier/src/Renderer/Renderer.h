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

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawQuad(const glm::vec3& position, float size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawQuad(const glm::vec2& position, float size, const glm::vec4& color, float rotation = 0.0f);

		static void DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture);
		static void DrawTexture(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float rotation = 0.0f);

		static void DrawCircle(const glm::mat4& transform, const glm::vec4& color);
		static void DrawCircle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);




	private:
		Renderer2D() = delete;

	};

}