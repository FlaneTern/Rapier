#include "Rapier.h"
#include "RapierEntryPoint.h"

#include "Forehead.h"
#include "Layer/ForeheadLayer.h"
#include "Layer/BackgroundLayer.h"
#include "Geometry/Pentagon.h"
#include "ForeheadCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Forehead {


	glm::vec2 Forehead::s_CameraVelocity = { 0, 0 };
	float Forehead::s_CameraRotationVelocity = 0;

	Forehead::Forehead() {

		PushLayer(new BackgroundLayer());
		PushLayer(new ForeheadLayer());

		m_CameraController = std::make_shared<ForeheadCamera>();


		Rapier::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

	}

	Forehead::~Forehead() {

	}

	void Forehead::OnUpdate(Rapier::DeltaTime dt) {

		Rapier::RenderCommand::Clear();

		Rapier::Renderer2D::BeginScene(Rapier::Application::Get().m_CameraController->GetCamera());


	}

	void Forehead::PostUpdate() {

		Rapier::Renderer2D::EndScene();

	}
}

Rapier::Application* Rapier::CreateApplication() {
	return new Forehead::Forehead();
}