#pragma once
#include "entt.hpp"

#include "Scene/Scene.h"
#include "Scene/Components.h"

#include "Assets/Script/Script.h"

namespace Rapier 
{

	class RAPIER_API Entity 
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;


		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) 
		{
			RAPIER_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}


		template<typename T>
		T& GetComponent() 
		{
			RAPIER_CORE_ASSERT(HasComponent<T>(), "Entity already does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		uint64_t GetUUID()
		{
			return GetComponent<UUIDComponent>().Id;
		}

		template<typename T>
		bool HasComponent() 
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent() 
		{
			RAPIER_CORE_ASSERT(HasComponent<T>(), "Entity already does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& ResetComponent(Args&&... args) 
		{
			RemoveComponent<T>();
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}


		// Args is not needed. Is there a better way to specialize this?
		template<typename ...Args>
		NativeScriptComponent& AddComponent(Ref<EntityScript> script) 
		{
			RAPIER_CORE_ASSERT(!HasComponent<NativeScriptComponent>(), "Entity already has component!");
			auto& component = m_Scene->m_Registry.emplace<NativeScriptComponent>(m_EntityHandle);
			component.Bind(script, *this);
			component.Instance->OnCreate();
			return component;
		}

		template<>
		void RemoveComponent<NativeScriptComponent>() 
		{
			RAPIER_CORE_ASSERT(HasComponent<NativeScriptComponent>(), "Entity already does not have component!");
			auto& component = GetComponent<NativeScriptComponent>();
			component.Instance->OnDestroy();
			m_Scene->m_Registry.remove<NativeScriptComponent>(m_EntityHandle);
		}

		template<typename... Args>
		NativeScriptComponent& ResetComponent(Ref<EntityScript> script) 
		{
			RemoveComponent<NativeScriptComponent>();
			return AddComponent<NativeScriptComponent>(script);
		}


		template<typename ...Args>
		RigidBody2DComponent& AddComponent(RigidBody2DData data, RigidBody2DProperties properties) 
		{
			RAPIER_CORE_ASSERT(!HasComponent<RigidBody2DComponent>(), "Entity already has component!");
			auto rigidBody = m_Scene->CreateRigidBody(data, properties);
			auto& component = m_Scene->m_Registry.emplace<RigidBody2DComponent>(m_EntityHandle, rigidBody);
			return component;
		}

		template<typename ...Args>
		RigidBody2DComponent& AddComponent(RigidBody2DComponent& other) 
		{
			RAPIER_CORE_ASSERT(!HasComponent<RigidBody2DComponent>(), "Entity already has component!")
			auto rigidBody = m_Scene->CreateRigidBody(other.RigidBody->GetData(), other.RigidBody->GetProperties());
			auto& component = m_Scene->m_Registry.emplace<RigidBody2DComponent>(m_EntityHandle, rigidBody);
			return component;
		}

		/*
		* TODO : Remove and reset RigidBody2DComponent
		template<>
		void RemoveComponent<NativeScriptComponent>() {
			RAPIER_CORE_ASSERT(HasComponent<NativeScriptComponent>(), "Entity already does not have component!");
			auto& component = GetComponent<NativeScriptComponent>();
			component.Instance->OnDestroy();
			m_Scene->m_Registry.remove<NativeScriptComponent>(m_EntityHandle);
		}

		template<typename... Args>
		NativeScriptComponent& ResetComponent(Ref<EntityScript> script) {
			RemoveComponent<NativeScriptComponent>();
			return AddComponent<NativeScriptComponent>(script);
		}
		*/

		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		Scene* GetScene() const { return m_Scene; }

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}