#include "ipch.h"
#include "entt.hpp"
#include "Time/DeltaTime.h"
#include "Scene/Components.h"
#include "Scene/EntityScript.h"
#include "Assets/Script/Script.h"
#include "Scene/Scene.h"
#include "Time/Timer.h"

#include "Renderer/Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	template<typename ...Args>
	static void CopyComponents(Entity& src, Entity& dst) {
		([&] {
			if (src.HasComponent<Args>()) {
				auto& component = dst.AddComponent<Args>(src.GetComponent<Args>());
			}

			}(), ...);
	}

	template<typename ...Args>
	static void CopyNativeScriptComponent(Entity& src, Entity& dst) {
		if (src.HasComponent<NativeScriptComponent>()) {
			auto& srcComponent = src.GetComponent<NativeScriptComponent>();
			auto& dstComponent = dst.AddComponent<NativeScriptComponent>();
			bool isDone = false;

			([&] {
				if (isDone)
					return;

				Args script;
				bool instantiateScript = false;
				if (!srcComponent.Instance) {
					srcComponent.Instance = srcComponent.InstantiateScript();;
					instantiateScript = true;
				}

				if (srcComponent.Instance->GetName() == script.GetName()) {
					dstComponent.Bind<Args>();
					dstComponent.EnableOnUpdate = srcComponent.EnableOnUpdate;
					isDone = true;
				}

				if (instantiateScript) {
					srcComponent.DestroyScript(&srcComponent);
				}

				}(), ...);

		}
	}


	Ref<Scene> Scene::Copy(Ref<Scene> other) {
		if (!other)
			return nullptr;

		Ref<Scene> newScene = std::make_shared<Scene>();

		auto otherView = other->m_Registry.view<UUIDComponent>();
		for (auto otherEntity : otherView) {
			Entity rOtherEntity{ otherEntity, other.get()};
			UUID uuid = rOtherEntity.GetUUID();
			std::string name = rOtherEntity.GetComponent<TagComponent>().Tag;
			auto transform = rOtherEntity.GetComponent<TransformComponent>();

			Entity newEntity = newScene->LoadEntity(uuid, name);
			auto& newEntityTransform = newEntity.GetComponent<TransformComponent>();
			newEntityTransform = transform;

			CopyComponents<COMPONENTS_LIST>(rOtherEntity, newEntity);
			CopyNativeScriptComponent<ALL_ENTITY_SCRIPTS>(rOtherEntity, newEntity);
		}

		return newScene;
	}

	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<UUIDComponent>();
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	Entity Scene::LoadEntity(uint64_t uuid, const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<UUIDComponent>(uuid);
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity) {
		entity.DestroyScript();
		m_Registry.destroy(entity);
	}



	void Scene::OnUpdateRuntime(DeltaTime dt) {
		TIME_FUNCTION_INTERNAL(Scene::OnUpdateRuntime);

		// Run Entity Updates
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			for (auto entity : view) {
				auto& script = view.get<NativeScriptComponent>(entity);

				if (!script.Instance) {
					script.Instance = script.InstantiateScript();
					script.Instance->m_Entity = Entity{ entity, this };
					script.Instance->OnCreate();
				}

				if(script.EnableOnUpdate) script.Instance->OnUpdate(dt);
			}
		}


		// Update Camera
		glm::mat4 CameraViewProjection = glm::mat4(1.0f);
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) {
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary) {
					CameraViewProjection = camera.Camera.GetProjection() * glm::inverse(transform.GetTransform());
					break;
				}
			}
		}



		RenderScene(CameraViewProjection);
	}


	void Scene::OnUpdateEdit(DeltaTime dt, glm::mat4 camera) {
		TIME_FUNCTION_INTERNAL(Scene::OnUpdateEdit);

#if 0
		// Update Camera
		glm::mat4 CameraViewProjection = glm::mat4(1.0f);
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) {
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary) {
					CameraViewProjection = camera.Camera.GetProjection() * glm::inverse(transform.GetTransform());
					break;
				}
			}
		}
#endif


		RenderScene(camera);
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view) {
			auto& camera = view.get<CameraComponent>(entity);

			if (!camera.FixedAspectRatio) {
				camera.Camera.SetViewportSize(width, height);
			}
		}
	}


	Entity Scene::GetPrimaryCamera() {
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view) {
			auto& camera = view.get<CameraComponent>(entity);

			if (camera.Primary) {
				return Entity{ entity, this };
			}
		}

		// No Camera
		// Implement better default?
		return Entity{ (entt::entity)0xffffffff, this };
	}

	void Scene::SetPrimaryCamera(Entity& entity) {
		RAPIER_CORE_ASSERT(entity.HasComponent<CameraComponent>(), "Entity doesn't have camera component!");

		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view) {
			auto& camera = view.get<CameraComponent>(entity);

			camera.Primary = false;
		}

		entity.GetComponent<CameraComponent>().Primary = true;
	}

	void Scene::RenderScene(const glm::mat4& camera) {
		TIME_FUNCTION_INTERNAL(Scene::RenderScene);
		Renderer2D::BeginScene(camera);

		{
			auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : view) {
				const auto& [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawTexture(transform, sprite.Texture, sprite.Color, (int)entity);

			}

		}

		Renderer2D::EndScene();
	}


	void Scene::AddSelectedEntities(Entity& entity) { 
		m_SelectedEntities.insert(entity.GetUUID()); 
	}

	void Scene::ClearSelectedEntities() { 
		m_SelectedEntities.clear(); 
	}

	void Scene::RemoveSelectedEntities(Entity& entity) {
		auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entity.GetUUID());
		if (it != m_SelectedEntities.end())
			m_SelectedEntities.erase(it);
	}

	bool Scene::IsEntitySelected(Entity& entity) {
		auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entity.GetUUID());
		return it != m_SelectedEntities.end();
	}
}