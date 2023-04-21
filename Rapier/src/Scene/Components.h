#pragma once

#include "glm/glm.hpp"
#include "Scene/EntityScript.h"

#include "Camera/Camera.h"
#include "Assets/Texture/Texture.h"

namespace Rapier {

	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string() const { return Tag; }
	};

	struct TransformComponent {
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};


	struct SpriteRendererComponent {
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = nullptr;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& other) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color), Texture(nullptr) {}

		SpriteRendererComponent(Ref<Texture2D> texture)
			: Color({1.0f, 1.0f, 1.0f, 1.0f}), Texture(texture) {}

		SpriteRendererComponent(Ref<Texture2D> texture, const glm::vec4& color)
			: Color(color), Texture(texture) {}
	};


	struct NativeScriptComponent {
		EntityScript* Instance = nullptr;

		EntityScript* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind() {
			InstantiateScript = []() { return static_cast<EntityScript*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct CameraComponent {
		Camera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(float& left, float& right, float& bottom, float& top, float& nearClip, float &farClip)
			: Camera(left, right, bottom, top, nearClip, farClip) {}
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(const glm::mat4& cam)
			: Camera(cam) {}

	};

}