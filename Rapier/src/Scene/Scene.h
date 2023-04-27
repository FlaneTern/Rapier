#pragma once

#include "entt.hpp"

namespace Rapier {
	class Entity;
	class Scene {
	public:
		Entity CreateEntity(const std::string& name = "UnknownEntity");
		void DestroyEntity(Entity& entity);

		void OnUpdate(DeltaTime dt);

		void OnViewportResize(uint32_t width, uint32_t height);

		void SetPrimaryCamera(Entity& entity);

		const std::unordered_set<uint32_t>& GetSelectedEntities() const { return m_SelectedEntities; }
		void AddSelectedEntities(uint32_t entityId) { m_SelectedEntities.insert(entityId); }
		void ClearSelectedEntities() { m_SelectedEntities.clear(); }
		void RemoveSelectedEntities(uint32_t entityId) { 
			auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entityId);
			if (it != m_SelectedEntities.end())
				m_SelectedEntities.erase(it);
		}
		bool IsEntitySelected(uint32_t entityId) {
			auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entityId);
			return it != m_SelectedEntities.end();
		}

	private:
		friend class Entity;
		friend class EntityListPanel;

		entt::registry m_Registry;
		std::unordered_set<uint32_t> m_SelectedEntities;
	};
}