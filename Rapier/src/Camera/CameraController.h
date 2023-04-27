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
			auto& transformComponent = GetComponent<TransformComponent>();
			auto& projectionComponent = GetComponent<CameraComponent>().Camera;
			float projectionSize = projectionComponent.GetSize();

			if (Input::IsKeyPressed(RapierKey_UpArrow))    transformComponent.Translation.y += TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_DownArrow))  transformComponent.Translation.y -= TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_RightArrow)) transformComponent.Translation.x += TranslationSpeed * projectionSize * dt;
			if (Input::IsKeyPressed(RapierKey_LeftArrow))  transformComponent.Translation.x -= TranslationSpeed * projectionSize * dt;

			if (Input::IsKeyPressed(RapierKey_LeftBracket))  transformComponent.Rotation.z += RotationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_RightBracket)) transformComponent.Rotation.z -= RotationSpeed * dt;


			if (Input::IsKeyPressed(RapierKey_Equal)) projectionComponent.SetSize(std::max(projectionSize - projectionSize * 1.50f * dt,  0.5f));
			if (Input::IsKeyPressed(RapierKey_Minus)) projectionComponent.SetSize(std::min(projectionSize + projectionSize * 1.50f * dt, 15.0f));
		}
	};

}