#pragma once
#include "ipch.h"
#include "glm/glm.hpp"

namespace Rapier {
	class RAPIER_API Input {
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousePos();

		static void SetBlockKeyInput(bool enable);
		static void SetBlockMouseInput(bool enable);
	private:
	};
}