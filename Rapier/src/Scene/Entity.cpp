#include "ipch.h"
#include "Time/DeltaTime.h"
#include "entt.hpp"
#include "Scene/Scene.h"
#include "Entity.h"

#include "Scene/Components.h"

namespace Rapier {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene) {

	}

	void Entity::DestroyScript() {
		if (HasComponent<NativeScriptComponent>()) {
			auto& script = GetComponent<NativeScriptComponent>();
			if (script.Instance)
				script.DestroyScript(&script);
		}
	}




}