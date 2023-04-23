#pragma once
#include "entt.hpp"

#include "Scene/Scene.h"

namespace Rapier {

	class Scene;
	struct NativeScriptComponent;

	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;


		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			RAPIER_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}


		template<typename T>
		T& GetComponent() {
			RAPIER_CORE_ASSERT(HasComponent<T>(), "Entity already does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() {
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent() {
			RAPIER_CORE_ASSERT(HasComponent<T>(), "Entity already does not have component!");

			// Do this better ?? ////////////////////////////
			if(typeid(T) == typeid(NativeScriptComponent))
				DestroyScript();
			// Do this better ?? ////////////////////////////

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& ResetComponent(Args&&... args) {
			RemoveComponent<T>();
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		void DestroyScript();

		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }


	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}