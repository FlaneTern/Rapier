#pragma once


#include "Scene/Scene.h"

namespace Rapier {

	class EntityListPanel {
	public:
		EntityListPanel(Ref<Scene> scene)
			: m_ActiveScene(scene) {}

		void SetScene(Ref<Scene> scene);

		void OnImGuiRender();

	private:
		Ref<Scene> m_ActiveScene;
	};
}