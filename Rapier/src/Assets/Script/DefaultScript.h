#pragma once

#include "Core.h"
#include "Assets/Script/Script.h"
#include "Time/DeltaTime.h"





namespace Rapier {


	struct NativeScriptComponent;
	class Scene;
	class Entity;



	class RAPIER_API DefaultEntityScript : public EntityScript {
	protected:

		friend struct NativeScriptComponent;
		friend class Scene;
		friend class Entity;

		virtual void OnUpdate(DeltaTime dt) override;
		virtual void OnDestroy() override;
		virtual void OnCreate() override;

		template<typename T>
		T& GetComponent();


	public:
		virtual Ref<EntityScript> Clone() const override;
		virtual std::string GetName() const { return "DefaultEntityScript"; }
	};


	class RAPIER_API CameraController : public DefaultEntityScript {
		float TranslationSpeed = 0.5f;
		float RotationSpeed = 180.0f;

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(DeltaTime dt) override;

	public:
		virtual Ref<EntityScript> Clone() const override;
		virtual std::string GetName() const override { return "CameraController"; }
	};

	class RAPIER_API TextureControl : public DefaultEntityScript {
		float RotationSpeed = 135.0f;
		float TranslationSpeed = 2.0f;

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(DeltaTime dt) override;

	public:
		virtual Ref<EntityScript> Clone() const override;
		virtual std::string GetName() const override { return "TextureControl"; }
	};

	class RAPIER_API SquareControlX : public DefaultEntityScript {
		bool forward = true;

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(DeltaTime dt) override;

	public:
		virtual Ref<EntityScript> Clone() const override;
		virtual std::string GetName() const override { return "SquareControlX"; }
	};


	class RAPIER_API SquareControlY : public DefaultEntityScript {
		bool forward = true;

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(DeltaTime dt) override;

	public:
		virtual Ref<EntityScript> Clone() const override;
		virtual std::string GetName() const override { return "SquareControlY"; }
	};

}