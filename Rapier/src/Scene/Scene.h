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

	private:
		friend class Entity;
		friend class EntityListPanel;
		entt::registry m_Registry;
	};
}