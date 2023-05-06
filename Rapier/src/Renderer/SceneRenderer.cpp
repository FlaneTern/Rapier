#include "ipch.h"

#include "Renderer/SceneRenderer.h"

#include "Renderer/DebugRenderer.h"
#include "Renderer/Renderer.h"

namespace Rapier 
{

	SceneRenderer::SceneRenderer()
		: m_Renderer2D(std::make_shared<Renderer2D>()), m_DebugRenderer(std::make_shared<DebugRendererIMPL>())
	{
		Init();
	}

	SceneRenderer::~SceneRenderer()
	{
		Shutdown();
	}

	void SceneRenderer::Init() 
	{

	}

	void SceneRenderer::Shutdown() 
	{

	}


	void SceneRenderer::BeginScene(const glm::mat4& camera) 
	{
		RAPIER_CORE_ASSERT(!m_StartedScene, "Scene has already started !");

		m_StartedScene = true;
		m_SceneData.reset(new SceneData(camera));

		m_Renderer2D->SetSceneData(m_SceneData);
	}

	void SceneRenderer::EndScene() 
	{

		m_StartedScene = false;
	}

}