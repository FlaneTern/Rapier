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
		float TranslationSpeed = 0.5f;
		float RotationSpeed = 180.0f;


		virtual void OnUpdate(DeltaTime dt) override {
			auto& transform = GetComponent<TransformComponent>().Transform;
			auto& projection = GetComponent<CameraComponent>().Camera;
			float projectionSize = projection.GetSize();

			if (Input::IsKeyPressed(RapierKey_UpArrow)) transform[3][1] += TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_DownArrow)) transform[3][1] -= TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_RightArrow)) transform[3][0] += TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_LeftArrow)) transform[3][0] -= TranslationSpeed * projectionSize * dt;

			if (Input::IsKeyPressed(RapierKey_LeftBracket))  transform = glm::rotate(transform, glm::radians(RotationSpeed * dt), glm::vec3(0, 0, 1));
			if (Input::IsKeyPressed(RapierKey_RightBracket)) transform = glm::rotate(transform, glm::radians(-RotationSpeed * dt), glm::vec3(0, 0, 1));


			if (Input::IsKeyPressed(RapierKey_Equal)) projection.SetSize(std::max(projectionSize - projectionSize * 1.50f * dt,  0.5f));
			if (Input::IsKeyPressed(RapierKey_Minus)) projection.SetSize(std::min(projectionSize + projectionSize * 1.50f * dt, 15.0f));
		}
	};

}