#pragma once


#include "Scene/Scene.h"

namespace Rapier 
{

	class Panel
	{
	public:
		Panel() {}
		Panel(Ref<Scene> scene)
			: m_ActiveScene(scene) {}

		void SetScene(Ref<Scene> scene) {
			m_ActiveScene = scene;
		}

		virtual void OnImGuiRender() = 0;

	protected:

		Ref<Scene> m_ActiveScene;
	};
}