#include "Irene.h"

class ExampleLayer : public IRENE::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		
	}

	void OnEvent(IRENE::Event& event) override {
		IRENE_INFO("{0}", event);
	}
};

class Forehead : public IRENE::Application {
public:
	Forehead() {
		PushLayer(new ExampleLayer());
		PushOverlay(new IRENE::ImGuiLayer);
	}

	~Forehead() {

	}


};

IRENE::Application* IRENE::CreateApplication() {
	return new Forehead();
}