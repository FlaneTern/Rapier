#pragma once
#include "ipch.h"

namespace Rapier {
	class RAPIER_API Input {
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();

		static void SetBlockKeyInput(bool enable);
		static void SetBlockMouseInput(bool enable);
	private:
	};
}