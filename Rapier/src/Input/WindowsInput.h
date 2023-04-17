#pragma once

#include "Input.h"

namespace Rapier {
	class RAPIER_API WindowsInput : public Input {
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePosImpl() override;
	};
}