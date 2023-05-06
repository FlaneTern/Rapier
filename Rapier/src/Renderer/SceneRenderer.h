#pragma once

#include "Renderer/RenderCommand.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Assets/AssetManager.h"

#include "Renderer/Renderer.h"

namespace Rapier {

	struct SceneData 
	{
		SceneData(const glm::mat4& camera) : ViewProjectionMatrix(camera) {}
		glm::mat4 ViewProjectionMatrix;
	};

	class DebugRenderer;


	class RAPIER_API SceneRenderer 
	{
	public:
		SceneRenderer();
		~SceneRenderer();

		Ref<Renderer2D> Get2DRenderer() { return m_Renderer2D; }


		void BeginScene(const glm::mat4& camera);
		void EndScene();

		void Init();
		void Shutdown();

		Ref<SceneData> GetSceneData() { return m_SceneData; }

	private:

		Ref<Renderer2D> m_Renderer2D;

		Ref<SceneData> m_SceneData;

		bool m_StartedScene = false;

#ifdef RAPIER_DEBUG
	public:
		Ref<DebugRendererIMPL> GetDebugRenderer() { return m_DebugRenderer; }
	private:
		Ref<DebugRendererIMPL> m_DebugRenderer;
#else
	public:
		Ref<DebugRendererIMPL> GetDebugRenderer() {}
#endif
	};

}