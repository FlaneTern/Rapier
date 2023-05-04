//#include "Rapier.h"
#include "Forehead.h"
#if 0
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

//Rapier::Application* Rapier::CreateApplication() {
//	return new Forehead::Forehead();
//}
#else



namespace Forehead {


	void DummyScript::OnUpdate(Rapier::DeltaTime dt) {
		SetRotation(GetRotation() + glm::vec3{0.0f, 135.0f * dt, 0.0f});
	}
	void DummyScript::OnCreate() {

	}
	void DummyScript::OnDestroy() {

	}


	void DummyScript2::OnUpdate(Rapier::DeltaTime dt) {
		SetScale(GetScale() * (1 + dt));

		Rapier::Renderer2D::DrawLine({ 0.0f, 0.0f, 4.0f }, { 1.0f, 1.0f, 4.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });

		RAPIER_INFO("DUMMY2ONUPDATE!!");
	}
	void DummyScript2::OnCreate() {

	}
	void DummyScript2::OnDestroy() {

	}
}


namespace Rapier {

	extern "C" RAPIER_SCRIPT_API EntityScriptContainer __stdcall EntityScriptFactory() {
		EntityScriptContainer container;
		container.m_Scripts.push_back(std::make_shared<Forehead::DummyScript>());
		container.m_Scripts.push_back(std::make_shared<Forehead::DummyScript2>());
		return container;
	}

}

#endif