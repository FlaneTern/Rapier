#include "ipch.h"
#include "entt.hpp"
#include "Time/DeltaTime.h"
#include "Scene/Components.h"
#include "Scene/EntityScript.h"
#include "Scene/Scene.h"

#include "Renderer/Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity) {
		entity.DestroyScript();
		m_Registry.destroy(entity);
	}



	void Scene::OnUpdate(DeltaTime dt) {

		RenderCommand::Clear();

		// Run Entity Updates
		{
			auto group = m_Registry.view<NativeScriptComponent>();
			for (auto entity : group) {
				auto& script = group.get<NativeScriptComponent>(entity);

				if (!script.Instance) {
					script.Instance = script.InstantiateScript();
					script.Instance->m_Entity = Entity{ entity, this };
					script.Instance->OnCreate();
				}

				if(script.Instance->EnableOnUpdate) script.Instance->OnUpdate(dt);
			}
		}


		// Update Camera
		glm::mat4 CameraViewProjection = glm::mat4(1.0f);
		{
			auto group = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : group) {
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary) {
					auto pro = camera.Camera.GetProjection();
					CameraViewProjection = camera.Camera.GetProjection() * glm::inverse(transform.Transform);
					break;
				}
			}
		}



		// Render
		Renderer2D::BeginScene(CameraViewProjection);
		
		{
			auto group = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : group) {
				const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				if (sprite.Texture)
					Renderer2D::DrawTexture(transform, sprite.Texture);
				else
					Renderer2D::DrawQuad(transform, sprite.Color);

			}

		}

		Renderer2D::EndScene();
	}



	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		auto group = m_Registry.view<CameraComponent>();

		for (auto entity : group) {
			auto& camera = group.get<CameraComponent>(entity);

			if (!camera.FixedAspectRatio) {
				camera.Camera.SetViewportSize(width, height);
			}
		}
	}


	void Scene::SetPrimaryCamera(Entity& entity) {
		auto group = m_Registry.view<CameraComponent>();

		for (auto entity : group) {
			auto& camera = group.get<CameraComponent>(entity);

			camera.Primary = false;
		}

		entity.GetComponent<CameraComponent>().Primary = true;
	}
}