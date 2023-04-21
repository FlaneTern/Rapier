#pragma once

#include "Scene/EntityScript.h"
#include "Time/DeltaTime.h"
#include "Input.h"
#include "Keycode/RapierKeycode.h"
#include "Scene/Components.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Rapier {

	class CameraController : public EntityScript {
		float TranslationSpeed = 2.0f;
		float RotationSpeed = 180.0f;


		virtual void OnUpdate(DeltaTime dt) override {
			auto& transform = GetComponent<TransformComponent>().Transform;

			if (Input::IsKeyPressed(RapierKey_UpArrow)) transform[3][1] += TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_DownArrow)) transform[3][1] -= TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_RightArrow)) transform[3][0] += TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_LeftArrow)) transform[3][0] -= TranslationSpeed * dt;

			if (Input::IsKeyPressed(RapierKey_O)) transform = glm::rotate(transform, glm::radians(RotationSpeed * dt), glm::vec3(0, 0, 1));
			if (Input::IsKeyPressed(RapierKey_P)) transform = glm::rotate(transform, glm::radians(-RotationSpeed * dt), glm::vec3(0, 0, 1));
		}
	};

}