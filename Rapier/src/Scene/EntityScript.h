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


	protected:
		friend class Scene;

		virtual void OnCreate() {}
		virtual void OnUpdate(DeltaTime dt) {}
		virtual void OnDestroy() {}

	private:
		friend class Scene;
		Entity m_Entity;
		
	};
}