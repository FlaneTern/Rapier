#pragma once

#include "Scene/Entity.h"

namespace Rapier {

	class EntityScript {
	public:
		virtual ~EntityScript() {}


		template<typename T>
		T& GetComponent() {
			return m_Entity.GetComponent<T>();
		}

		virtual std::string GetName() { return "EntityScript"; }

	protected:
		friend class Scene;

		virtual void OnUpdate(DeltaTime dt) {}
		virtual void OnDestroy() {}
		virtual void OnCreate() {}
		Entity m_Entity;
		
	};
}