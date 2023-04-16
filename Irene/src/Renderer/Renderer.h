#pragma once

#include "Renderer/RenderCommand.h"
#include "Camera/Camera.h"
#include "Renderer/Shader.h"

namespace IRENE {

	struct SceneData {
		SceneData(const OrthographicCamera& camera) : ViewProjectionMatrix(camera.GetViewProjectionMatrix()) {}
		glm::mat4 ViewProjectionMatrix;
	};


	class Renderer {
	public:

		static void BeginScene(const OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


		static void Create();
		Renderer(const Renderer& other) = delete;


	private:
		Renderer();

		static std::unique_ptr<Renderer> s_Renderer;

		std::unique_ptr<SceneData> m_SceneData;
		bool m_StartedScene;
		
	};

}