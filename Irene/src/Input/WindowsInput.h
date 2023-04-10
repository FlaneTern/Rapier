#pragma once

#include "Input.h"

namespace IRENE {
	class IRENE_API WindowsInput : public Input {
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePosImpl() override;
	};
}