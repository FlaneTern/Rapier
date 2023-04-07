#pragma once
#include "Core.h"

namespace IRENE {

	class IRENE_API Application
	{

	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* CreateApplication();
}

	