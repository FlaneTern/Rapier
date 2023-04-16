#pragma once
#include "Irene.h"

namespace Forehead {

	class Forehead : public IRENE::Application {
	public:
		Forehead();

		~Forehead();

		void OnUpdate(IRENE::DeltaTime dt) override;



		static glm::vec2 s_CameraVelocity;
		static float s_CameraRotationVelocity;
	private:
	};
}