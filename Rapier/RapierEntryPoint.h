#pragma once



extern Rapier::Application* Rapier::CreateApplication();


int main(int argc, char** argv)
{
	Rapier::Log::Init();
	RAPIER_CORE_INFO("Initializing Rapier");

	auto app = Rapier::CreateApplication();
	app->Run();
	delete app;
}

