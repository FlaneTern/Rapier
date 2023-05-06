#include "Rapier.h"
#include "Forehead.h"



namespace Forehead
{


	void DummyScript::OnUpdate(Rapier::DeltaTime dt)
	{
		SetRotation(GetRotation() + glm::vec3{0.0f, 135.0f * dt, 0.0f});
		Rapier::DebugRenderer::DrawLine(GetScene(), { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
	}

	void DummyScript::OnCreate() {

	}

	void DummyScript::OnDestroy() {

	}


	void DummyScript2::OnUpdate(Rapier::DeltaTime dt) 
	{
		SetScale(GetScale() * (1 + dt));
		RAPIER_INFO("DUMMY2ONUPDATE!!");
	}

	void DummyScript2::OnCreate()
	{

	}

	void DummyScript2::OnDestroy() 
	{

	}
}


namespace Rapier 
{

	extern "C" RAPIER_SCRIPT_API EntityScriptContainer __stdcall EntityScriptFactory() 
	{
		EntityScriptContainer container;
		container.m_Scripts.push_back(std::make_shared<Forehead::DummyScript>());
		container.m_Scripts.push_back(std::make_shared<Forehead::DummyScript2>());
		return container;
	}

}
