#pragma once



extern IRENE::Application* IRENE::CreateApplication();


int main(int argc, char** argv) {
	auto app = IRENE::CreateApplication();
	app->run();
	delete app;
}

