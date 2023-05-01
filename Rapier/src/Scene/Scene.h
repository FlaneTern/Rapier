#pragma once

#include "Time/DeltaTime.h"

#include "glm/glm.hpp"
#include "entt.hpp"

namespace Rapier {
	class Entity;
	class SceneSerializer;

	class Scene {
	public:
		Entity CreateEntity(const std::string& name = "UnknownEntity");
		Entity LoadEntity(uint64_t uuid, const std::string& name = "UnknownEntity");
		void DestroyEntity(Entity& entity);

		void OnUpdateRuntime(DeltaTime dt);
		void OnUpdateEdit(DeltaTime dt, glm::mat4 camera);

		void OnViewportResize(uint32_t width, uint32_t height);

		void SetPrimaryCamera(Entity& entity);
		Entity GetPrimaryCamera();

		const std::unordered_set<uint32_t>& GetSelectedEntities() const { return m_SelectedEntities; }
		void AddSelectedEntities(Entity& entity);
		void ClearSelectedEntities();
		void RemoveSelectedEntities(Entity& entity);
		bool IsEntitySelected(Entity& entity);
		
		static Ref<Scene> Copy(Ref<Scene> other);
	private:
		friend class Entity;
		friend class EntityListPanel;
		friend class SceneSerializer;

		void RenderScene(const glm::mat4& camera);

		entt::registry m_Registry;
		std::unordered_set<uint32_t> m_SelectedEntities;
	};
}