#pragma once

#include "Core.h"
#include "Time/DeltaTime.h"

#include "Log.h"
#include "Assets/Texture/Texture.h"

#include "glm/glm.hpp"

namespace Rapier 
{

	struct NativeScriptComponent;
	class Scene;
	class Entity;


	
	class RAPIER_API EntityScript 
	{
	public:
		virtual Ref<EntityScript> Clone() const;
		virtual std::string GetName() const;

	protected:

		friend struct NativeScriptComponent;
		friend class Scene;
		friend class Entity;

		virtual void OnUpdate(DeltaTime dt);
		virtual void OnDestroy();
		virtual void OnCreate();


	protected:
		
		virtual uint64_t GetUUID() const final;
		virtual std::string GetTag() const final;
		virtual glm::vec3 GetTranslation() const final;
		virtual glm::vec3 GetRotation() const final;
		virtual glm::vec3 GetScale() const final;
		virtual glm::vec4 GetColor() const final;
		virtual Ref<Texture2D> GetTexture() const final;
		virtual glm::mat4 GetCameraProjection() const final;
		
		virtual Scene* GetScene() const final;

		virtual void SetTranslation(const glm::vec3& translation) final;
		virtual void SetRotation(const glm::vec3& rotation) final;
		virtual void SetScale(const glm::vec3& scale) final;
		virtual void SetColor(const glm::vec4& color) final;
		virtual void SetTexture(Ref<Texture2D> texture) final;
		virtual void SetCameraFixedAspectRatio(bool fixed) final;
		virtual void SetCameraAsPrimary() final;


		Ref<Entity> m_Entity;

	private:
	};
	

	class RAPIER_API EntityScriptContainer 
	{
	public:
		static EntityScriptContainer s_EntityScriptContainer;
		std::vector<Ref<EntityScript>> m_Scripts;
	};

#pragma warning(suppress: 4190)
	extern "C" RAPIER_SCRIPT_API EntityScriptContainer __stdcall EntityScriptFactory();

}