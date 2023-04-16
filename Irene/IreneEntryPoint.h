#pragma once



extern IRENE::Application* IRENE::CreateApplication();


int main(int argc, char** argv) {
	IRENE::Log::Init();
	IRENE_CORE_INFO("Initializing Irene");

	auto app = IRENE::CreateApplication();
	app->Run();
	delete app;
}

