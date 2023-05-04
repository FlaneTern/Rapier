#pragma once

#include "Scene/Scene.h"

namespace Rapier {

	class RAPIER_API SceneSerializer {
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);

	private:
		Ref<Scene> m_Scene;
	};

}