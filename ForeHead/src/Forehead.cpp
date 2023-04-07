#include "Irene.h"

class Forehead : public IRENE::Application {
public:
	Forehead() {

	}

	~Forehead() {

	}


};

IRENE::Application* IRENE::CreateApplication() {
	return new Forehead();
}