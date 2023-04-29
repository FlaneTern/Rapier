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


			if (Input::IsKeyPressed(RapierKey_Equal)) projectionComponent.SetSize(std::max(projectionSize - projectionSize * 1.50f * dt, 0.5f));
			if (Input::IsKeyPressed(RapierKey_Minus)) projectionComponent.SetSize(std::min(projectionSize + projectionSize * 1.50f * dt, 15.0f));
		}

	public:
		virtual std::string GetName() { return "CameraController"; }
	};

	class TextureControl : public EntityScript {
		float RotationSpeed = 135.0f;
		float TranslationSpeed = 2.0f;


		virtual void OnUpdate(DeltaTime dt) override {

			auto& transform = GetComponent<TransformComponent>();

			transform.Rotation.z += RotationSpeed * dt;
			if (transform.Rotation.z >= 360.0f)
				transform.Rotation.z -= 360.0f;


			if (Input::IsKeyPressed(RapierKey_W)) transform.Translation.y += TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_S)) transform.Translation.y -= TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_D)) transform.Translation.x += TranslationSpeed * dt;
			if (Input::IsKeyPressed(RapierKey_A)) transform.Translation.x -= TranslationSpeed * dt;
		}

	public:
		virtual std::string GetName() { return "TextureControl"; }
	};

	class SquareControlX : public EntityScript {
		bool forward = true;

		virtual void OnUpdate(DeltaTime dt) override {
			auto& transform = GetComponent<TransformComponent>();
			float& x = transform.Translation.x;

			if (x > 3.0f)
				forward = false;
			else if (x < -3.0f)
				forward = true;


			if (forward)
				x += 3.0f * dt;
			else
				x -= 3.0f * dt;
		}

	public:
		virtual std::string GetName() { return "SquareControlX"; }
	};


	class SquareControlY : public EntityScript {
		bool forward = true;

		virtual void OnUpdate(DeltaTime dt) override {
			auto& transform = GetComponent<TransformComponent>();
			float& y = transform.Translation.y;

			if (y > 3.0f)
				forward = false;
			else if (y < -3.0f)
				forward = true;


			if (forward)
				y += 3.0f * dt;
			else
				y -= 3.0f * dt;
		}

	public:
		virtual std::string GetName() { return "SquareControlY"; }
	};

#define DEFAULT_ENTITY_SCRIPTS EntityScript, CameraController, TextureControl, SquareControlX, SquareControlY

#ifndef ENTITY_SCRIPTS
#define ENTITY_SCRIPTS
#define ALL_ENTITY_SCRIPTS DEFAULT_ENTITY_SCRIPTS
#else
#define ALL_ENTITY_SCRIPTS  ENTITY_SCRIPTS, DEFAULT_ENTITY_SCRIPTS
#endif
}