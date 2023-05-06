#pragma once

#include "Time/DeltaTime.h"
#include "Random/UUID.h"
#include "Physics/PhysicsWorld2D.h"

#include "glm/glm.hpp"
#include "entt.hpp"

#include "Renderer/SceneRenderer.h"


namespace Rapier 
{
	class Entity;
	class SceneSerializer;

	class RAPIER_API Scene 
	{
	public:

		Scene();

		Entity CreateEntity(const std::string& name = "UnknownEntity");
		Entity LoadEntity(uint64_t uuid, const std::string& name = "UnknownEntity");
		void DestroyEntity(Entity& entity);

		void OnUpdateRuntime(DeltaTime dt);
		void OnUpdateEdit(DeltaTime dt, glm::mat4 camera);

		void OnViewportResize(uint32_t width, uint32_t height);

		void SetPrimaryCamera(Entity& entity);
		Entity GetPrimaryCamera();

		const std::unordered_set<uint64_t>& GetSelectedEntities() const { return m_SelectedEntities; }
		void AddSelectedEntities(Entity& entity);
		void ClearSelectedEntities();
		void RemoveSelectedEntities(Entity& entity);
		bool IsEntitySelected(Entity& entity);
		
		static Ref<Scene> Copy(Ref<Scene> other);

		Ref<RigidBody2D> CreateRigidBody(RigidBody2DData data, RigidBody2DProperties properties);

		Ref<SceneRenderer> GetSceneRenderer() { return m_Renderer; }
		Ref<Renderer2D> Get2DRenderer() { return m_Renderer->Get2DRenderer(); }

#ifdef RAPIER_DEBUG
		Ref<DebugRendererIMPL> GetDebugRenderer() { return m_Renderer->GetDebugRenderer(); }
#else
		Ref<DebugRendererIMPL> GetDebugRenderer() {}
#endif
	private:
		friend class Entity;
		friend class EntityListPanel;
		friend class SceneSerializer;

		void RenderScene(const glm::mat4& camera);

		entt::registry m_Registry;
		std::unordered_set<uint64_t> m_SelectedEntities;

		PhysicsWorld2D m_PhysicsWorld;

		Ref<SceneRenderer> m_Renderer;
	};
}