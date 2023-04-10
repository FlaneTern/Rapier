#pragma once



extern IRENE::Application* IRENE::CreateApplication();


int main(int argc, char** argv) {
	IRENE::Log::Init();
	IRENE_CORE_WARN("HALOOO");
	IRENE_WARN("weEAFE");

	auto app = IRENE::CreateApplication();
	app->Run();
	delete app;
}

