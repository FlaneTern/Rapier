#include "ipch.h"

#include "Scene/Components.h"
#include "Assets/Script/Script.h"
#include "Scene/Entity.h"

namespace Rapier
{
	void NativeScriptComponent::Bind(Ref<EntityScript> script, Entity& entity) 
	{
		Instance = script->Clone();
		Instance->m_Entity = std::make_shared<Entity>(entity);
	}
}