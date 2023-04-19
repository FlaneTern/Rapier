#pragma once

#include "Renderer/RenderCommand.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Assets/AssetManager.h"


namespace Rapier {

	struct SceneData {
		SceneData(const OrthographicCamera& camera) : ViewProjectionMatrix(camera.GetViewProjectionMatrix()) {}
		glm::mat4 ViewProjectionMatrix;
	};


	class Renderer {
	public:

		static void BeginScene(const OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


		static void Create();
		Renderer(const Renderer& other) = delete;


	private:
		Renderer();

		static Scope<Renderer> s_Renderer;

		Scope<SceneData> m_SceneData;
		bool m_StartedScene;
		
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	class Renderer2D {
	public:

		static void BeginScene(const OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


		static void Create();
		Renderer2D(const Renderer2D& other) = delete;




		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawTexture(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture);
		static void DrawTexture(const glm::vec3& position, const glm::vec2& size, AssetManager::DefaultTexture2DId id);




	private:
		Renderer2D();

		static Scope<Renderer2D> s_Renderer2D;

		Scope<SceneData> m_SceneData;
		bool m_StartedScene;

	};

}