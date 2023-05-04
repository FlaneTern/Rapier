#pragma once
#include "Rapier.h"
#if 0
namespace Forehead {

	class Forehead : public Rapier::Application {
	public:
		Forehead();

		~Forehead();

		void OnUpdate(Rapier::DeltaTime dt) override;
		void PostUpdate() override;

		static glm::vec2 s_CameraVelocity;
		static float s_CameraRotationVelocity;


	private:

	};
}

#else


namespace Forehead {

	class DummyScript : public Rapier::EntityScript
	{
		virtual void OnUpdate(Rapier::DeltaTime dt) override;
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual std::string GetName() const override { return "DummyScript"; }
		virtual Rapier::Ref<EntityScript> Clone() const override { return std::make_shared<DummyScript>(*this); };
	};

	class DummyScript2 : public Rapier::EntityScript
	{
		virtual void OnUpdate(Rapier::DeltaTime dt) override;
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual std::string GetName() const override { return "DummyScript2"; }
		virtual Rapier::Ref<EntityScript> Clone() const override { return std::make_shared<DummyScript2>(*this); };
	};
}


#endif