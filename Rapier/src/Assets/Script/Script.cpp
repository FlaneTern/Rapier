#include "ipch.h"
#include "Assets/Script/Script.h"
#include "Assets/Script/DefaultScript.h"
#include "Input.h"
#include "Keycode/RapierKeycode.h"
#include "Scene/Entity.h"

namespace Rapier 
{
	EntityScriptContainer EntityScriptContainer::s_EntityScriptContainer;

	uint64_t EntityScript::GetUUID() const 
	{
		return m_Entity->GetUUID();
	}

	std::string EntityScript::GetTag() const 
	{
		return m_Entity->GetComponent<TagComponent>().Tag;
	}

	glm::vec3 EntityScript::GetTranslation() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		return m_Entity->GetComponent<TransformComponent>().Translation;
	}

	glm::vec3 EntityScript::GetRotation() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		return m_Entity->GetComponent<TransformComponent>().Rotation;
	}

	glm::vec3 EntityScript::GetScale() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		return m_Entity->GetComponent<TransformComponent>().Scale;
	}

	glm::vec4 EntityScript::GetColor() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<SpriteRendererComponent>(), "Entity doesn't have Sprite Renderer Component !");
		return m_Entity->GetComponent<SpriteRendererComponent>().Color;
	}

	Ref<Texture2D> EntityScript::GetTexture() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<SpriteRendererComponent>(), "Entity doesn't have Sprite Renderer Component !");
		return m_Entity->GetComponent<SpriteRendererComponent>().Texture;
	}

	glm::mat4 EntityScript::GetCameraProjection() const 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<CameraComponent>(), "Entity doesn't have Camera Component !");
		return m_Entity->GetComponent<CameraComponent>().Camera.GetProjection();
	}

	Scene* EntityScript::GetScene() const 
	{
		return m_Entity->GetScene();
	}



	void EntityScript::SetTranslation(const glm::vec3& translation) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		auto& transform = m_Entity->GetComponent<TransformComponent>();
		transform.Translation = translation;
	}

	void EntityScript::SetRotation(const glm::vec3& rotation) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		auto& transform = m_Entity->GetComponent<TransformComponent>();
		transform.Rotation = rotation;
	}

	void EntityScript::SetScale(const glm::vec3& scale) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<TransformComponent>(), "Entity doesn't have Transform Component !");
		auto& transform = m_Entity->GetComponent<TransformComponent>();
		transform.Scale = scale;
	}

	void EntityScript::SetColor(const glm::vec4& color) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<SpriteRendererComponent>(), "Entity doesn't have Sprite Renderer Component !");
		auto& src = m_Entity->GetComponent<SpriteRendererComponent>();
		src.Color = color;
	}

	void EntityScript::SetTexture(Ref<Texture2D> texture) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<SpriteRendererComponent>(), "Entity doesn't have Sprite Renderer Component !");
		auto& src = m_Entity->GetComponent<SpriteRendererComponent>();
		src.Texture = texture;
	}

	void EntityScript::SetCameraFixedAspectRatio(bool fixed) 
	{
		RAPIER_CORE_ASSERT(m_Entity->HasComponent<CameraComponent>(), "Entity doesn't have Camera Component !");
		auto& src = m_Entity->GetComponent<CameraComponent>();
		src.FixedAspectRatio = fixed;
	}

	void EntityScript::SetCameraAsPrimary() 
	{
		// TODO
	}


	void EntityScript::OnUpdate(DeltaTime dt) 
	{

	}

	void EntityScript::OnDestroy() 
	{

	}

	void EntityScript::OnCreate() 
	{

	}


	Ref<EntityScript> EntityScript::Clone() const 
	{
		return std::make_shared<EntityScript>(*this);
	}

	std::string EntityScript::GetName() const 
	{
		return "Entity Script";
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	T& DefaultEntityScript::GetComponent() 
	{
		return m_Entity->GetComponent<T>();
	}

	Ref<EntityScript> DefaultEntityScript::Clone() const 
	{
		return std::make_shared<DefaultEntityScript>(*this);
	}

	void DefaultEntityScript::OnDestroy() { RAPIER_CORE_INFO("Default Entity Script : OnDestroy()"); }
	void DefaultEntityScript::OnCreate() { RAPIER_CORE_INFO("Default Entity Script : OnCreate()"); }
	void DefaultEntityScript::OnUpdate(DeltaTime dt) { RAPIER_CORE_INFO("Default Entity Script : OnUpdate()"); }



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Ref<EntityScript> CameraController::Clone() const 
	{
		return std::make_shared<CameraController>(*this);
	}

	void CameraController::OnCreate() {}
	void CameraController::OnDestroy() {}

	void CameraController::OnUpdate(DeltaTime dt) 
	{
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


	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Ref<EntityScript> TextureControl::Clone() const 
	{
		return std::make_shared<TextureControl>(*this);
	}

	void TextureControl::OnCreate() {}
	void TextureControl::OnDestroy() {}

	void TextureControl::OnUpdate(DeltaTime dt) 
	{

		auto& transform = GetComponent<TransformComponent>();

		transform.Rotation.z += RotationSpeed * dt;
		if (transform.Rotation.z >= 360.0f)
			transform.Rotation.z -= 360.0f;


		if (Input::IsKeyPressed(RapierKey_W)) transform.Translation.y += TranslationSpeed * dt;
		if (Input::IsKeyPressed(RapierKey_S)) transform.Translation.y -= TranslationSpeed * dt;
		if (Input::IsKeyPressed(RapierKey_D)) transform.Translation.x += TranslationSpeed * dt;
		if (Input::IsKeyPressed(RapierKey_A)) transform.Translation.x -= TranslationSpeed * dt;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Ref<EntityScript> SquareControlX::Clone() const 
	{
		return std::make_shared<SquareControlX>(*this);
	}

	void SquareControlX::OnCreate() {}
	void SquareControlX::OnDestroy() {}

	void SquareControlX::OnUpdate(DeltaTime dt) 
	{
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




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Ref<EntityScript> SquareControlY::Clone() const 
	{
		return std::make_shared<SquareControlY>(*this);
	}

	void SquareControlY::OnCreate() {}
	void SquareControlY::OnDestroy() {}

	void SquareControlY::OnUpdate(DeltaTime dt) 
	{
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

}