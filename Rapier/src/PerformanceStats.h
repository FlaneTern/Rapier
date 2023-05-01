#pragma once

#include "Time/Timer.h"

namespace Rapier {
	class Renderer2D;
	class ImGuiLayer;

	struct FunctionTimeData {
		std::string FunctionName = "";
		float FunctionTimeMS = 0.0f;
	};

	struct FrameData {
		std::vector<FunctionTimeData> FunctionTime;
	};

	struct RendererData {
		uint32_t QuadCount = 0;
		uint32_t CircleCount = 0;
		uint32_t LineCount = 0;
		uint32_t TextureCount = 0;
		uint32_t DrawCallCount = 0;
	};

	class PerformanceStats {
	public:
		static void BeginFrame();

		static void AddFunctionTime(FunctionTimeData data);

	private:
		friend class Renderer2D;
		friend class ImGuiLayer;

		static FrameData s_CurrentFrameData;
		static RendererData s_CurrentRendererData;
	};
}