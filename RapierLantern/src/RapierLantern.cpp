#include "Rapier.h"
#include "RapierEntryPoint.h"

#include "RapierLantern.h"
#include "Layer/LanternLayer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "entt.hpp"

namespace Rapier 
{


	glm::vec2 s_CameraVelocity = { 0, 0 };
	float s_CameraRotationVelocity = 0;

	RapierLantern::RapierLantern()
	{

		PushLayer(new LanternLayer());

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

	}

	RapierLantern::~RapierLantern() 
	{

	}

	void RapierLantern::OnUpdate(DeltaTime dt) 
	{

	}

	void RapierLantern::PostUpdate()
	{

	}
}

Rapier::Application* Rapier::CreateApplication()
{
	return new Rapier::RapierLantern();
}