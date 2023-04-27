#pragma once

#include "glm/glm.hpp"

#include "Assets/AssetManager.h"

#include "Camera/Camera.h"
#include "Assets/Texture/Texture.h"

namespace Rapier {

	class EntityScript;

	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string() const { return Tag; }

		static constexpr std::string_view AddName = "Add Tag Component\0";
		static constexpr std::string_view RemoveName = "Remove Tag Component\0";
	};

	struct TransformComponent {
		//glm::mat4 Transform{ 1.0f };
		//TransformComponent(const glm::mat4& transform)
		//	: Transform(transform) {}

		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };


		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}


		glm::mat4 GetTransform() {
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), { 1, 0 ,0 })
				* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), { 0, 1 ,0 })
				* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), { 0, 0 ,1 });

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		operator glm::mat4 () { return GetTransform(); }

		static constexpr std::string_view AddName = "Add Transform Component\0";
		static constexpr std::string_view RemoveName = "Remove Transform Component\0";
	};


	struct SpriteRendererComponent {
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = AssetManager::GetWhiteTexture();

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& other) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color), Texture(AssetManager::GetWhiteTexture()) {}

		SpriteRendererComponent(Ref<Texture2D> texture)
			: Color({1.0f, 1.0f, 1.0f, 1.0f}), Texture(texture) {}

		SpriteRendererComponent(Ref<Texture2D> texture, const glm::vec4& color)
			: Color(color), Texture(texture) {}

		static constexpr std::string_view AddName = "Add Sprite Renderer Component\0";
		static constexpr std::string_view RemoveName = "Remove Sprite Renderer Component\0";
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

		static constexpr std::string_view AddName = "Add Native Script Component\0";
		static constexpr std::string_view RemoveName = "Remove Native Script Component\0";
	};

	struct CameraComponent {
		Camera Camera;
		bool Primary = false;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(float& left, float& right, float& bottom, float& top, float& nearClip, float &farClip)
			: Camera(left, right, bottom, top, nearClip, farClip) {}
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(const glm::mat4& cam)
			: Camera(cam) {}

		static constexpr std::string_view AddName = "Add Camera Component\0";
		static constexpr std::string_view RemoveName = "Remove Camera Component\0";
	};




#define COMPONENTS_LIST CameraComponent, SpriteRendererComponent
}