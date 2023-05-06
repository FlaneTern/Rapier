#include "ipch.h"
#include "entt.hpp"
#include "Time/DeltaTime.h"
#include "Scene/Components.h"
#include "Assets/Script/Script.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Time/Timer.h"

#include "Renderer/SceneRenderer.h"
#include "Renderer/Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Rapier 
{

	template<typename ...Args>
	static void CopyComponents(Entity& src, Entity& dst) 
	{
		([&] {

			if (src.HasComponent<Args>()) 
			{
				auto& component = dst.AddComponent<Args>(src.GetComponent<Args>());
			}

			}(), ...);
	}


	static void CopyNativeScriptComponent(Entity& src, Entity& dst) 
	{
		if (!src.HasComponent<NativeScriptComponent>())
			return;

		auto& srcComponent = src.GetComponent<NativeScriptComponent>();
		dst.AddComponent<NativeScriptComponent>(srcComponent.Instance->Clone());
	}

	static void CopyRigidBody2DComponent(Entity& src, Entity& dst) 
	{
		if (!src.HasComponent<RigidBody2DComponent>())
			return;

		auto& srcComponent = src.GetComponent<RigidBody2DComponent>();
		dst.AddComponent<RigidBody2DComponent>(srcComponent);
	}

	Scene::Scene()
		: m_Renderer(std::make_shared<SceneRenderer>()) 
	{
	}


	Ref<Scene> Scene::Copy(Ref<Scene> other) 
	{
		if (!other)
			return nullptr;

		Ref<Scene> newScene = std::make_shared<Scene>();

		newScene->m_PhysicsWorld = PhysicsWorld2D({0.0f, -9.8f});

		other->m_Registry.each(
			[&](auto entity) 
			{
				Entity rOtherEntity{ entity, other.get() };
				UUID uuid = rOtherEntity.GetUUID();
				std::string name = rOtherEntity.GetComponent<TagComponent>().Tag;
				auto transform = rOtherEntity.GetComponent<TransformComponent>();

				Entity newEntity = newScene->LoadEntity(uuid, name);
				auto& newEntityTransform = newEntity.GetComponent<TransformComponent>();
				newEntityTransform = transform;

				CopyComponents<COMPONENTS_LIST>(rOtherEntity, newEntity);
				CopyNativeScriptComponent(rOtherEntity, newEntity);
				CopyRigidBody2DComponent(rOtherEntity, newEntity);
			}
		);



		return newScene;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<UUIDComponent>();
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	Entity Scene::LoadEntity(uint64_t uuid, const std::string& name) 
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<UUIDComponent>(uuid);
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity)
	{
		if (entity.HasComponent<NativeScriptComponent>())
		{
			auto& script = entity.GetComponent<NativeScriptComponent>();
			script.Instance->OnDestroy();
		}
		m_Registry.destroy(entity);
	}



	void Scene::OnUpdateRuntime(DeltaTime dt)
	{
		TIME_FUNCTION_INTERNAL(Scene::OnUpdateRuntime);

		// Run Entity Updates
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			for (auto& entity : view) {
				auto& script = view.get<NativeScriptComponent>(entity);

				if (!script.IsCreated)
					script.Instance->OnCreate();

				if(script.EnableOnUpdate) 
					script.Instance->OnUpdate(dt);
			}
		}


		// Physics
		{
			m_PhysicsWorld.OnUpdate(dt);
			auto view = m_Registry.view<TransformComponent, RigidBody2DComponent>();

			for (auto entity : view) 
			{
				auto [transform, rigidBody] = view.get<TransformComponent, RigidBody2DComponent>(entity);

				transform.Translation.x = rigidBody.RigidBody->GetPosition().x;
				transform.Translation.y = rigidBody.RigidBody->GetPosition().y;


			}
		}

		// Update Camera
		glm::mat4 CameraViewProjection = glm::mat4(1.0f);
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) 
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary) 
				{
					CameraViewProjection = camera.Camera.GetProjection() * glm::inverse(transform.GetTransform());
					break;
				}
			}
		}



		RenderScene(CameraViewProjection);
	}


	void Scene::OnUpdateEdit(DeltaTime dt, glm::mat4 camera)
	{
		TIME_FUNCTION_INTERNAL(Scene::OnUpdateEdit);

		RenderScene(camera);
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height) 
	{
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);

			if (!camera.FixedAspectRatio) 
			{
				camera.Camera.SetViewportSize(width, height);
			}
		}
	}


	Entity Scene::GetPrimaryCamera() 
	{
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);

			if (camera.Primary)
			{
				return Entity{ entity, this };
			}
		}

		return Entity{ entt::null, this };
	}

	void Scene::SetPrimaryCamera(Entity& entity)
	{
		RAPIER_CORE_ASSERT(entity.HasComponent<CameraComponent>(), "Entity doesn't have camera component!");

		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view) 
		{
			auto& camera = view.get<CameraComponent>(entity);

			camera.Primary = false;
		}

		entity.GetComponent<CameraComponent>().Primary = true;
	}

	void Scene::RenderScene(const glm::mat4& camera) 
	{
		TIME_FUNCTION_INTERNAL(Scene::RenderScene);
		m_Renderer->BeginScene(camera);


		Ref<Renderer2D> renderer2D = Get2DRenderer();
		renderer2D->BeginScene();


		{
			auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : view) 
			{
				const auto& [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

				renderer2D->DrawTexture(transform, sprite.Texture, sprite.Color, (int)entity);

			}

		}

		renderer2D->EndScene();

		m_Renderer->GetDebugRenderer()->DebugFlush(m_Renderer->GetSceneData());

		m_Renderer->EndScene();
	}


	void Scene::AddSelectedEntities(Entity& entity)
	{ 
		m_SelectedEntities.insert(entity.GetUUID()); 
	}

	void Scene::ClearSelectedEntities() 
	{ 
		m_SelectedEntities.clear(); 
	}

	void Scene::RemoveSelectedEntities(Entity& entity)
	{
		auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entity.GetUUID());
		if (it != m_SelectedEntities.end())
			m_SelectedEntities.erase(it);
	}

	bool Scene::IsEntitySelected(Entity& entity)
	{
		auto it = std::find(m_SelectedEntities.begin(), m_SelectedEntities.end(), entity.GetUUID());
		return it != m_SelectedEntities.end();
	}

	Ref<RigidBody2D> Scene::CreateRigidBody(RigidBody2DData data, RigidBody2DProperties properties) 
	{
		 return m_PhysicsWorld.CreateRigidBody(data, properties);
	}
}