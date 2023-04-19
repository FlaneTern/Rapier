#pragma once
#include "Rapier.h"

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