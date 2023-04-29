#pragma once

namespace Rapier {

	struct FunctionTimeData {
		std::string FunctionName = "";
		float FunctionTimeMS = 0.0f;
	};

	struct FrameData {
		std::vector<FunctionTimeData> FunctionTime;
	};

	struct RendererData {
		uint32_t QuadCount = 0;
		uint32_t TextureCount = 0;
		uint32_t DrawCallCount = 0;
	};

	class PerformanceStats {
	public:
		static void BeginFrame();

		static void AddFunctionTime(FunctionTimeData data);
		static void AddQuadCount();
		static void AddTextureCount();
		static void AddDrawCallCount();

		static const FrameData& GetFrameData() { return s_CurrentFrameData; }
		static const RendererData& GetRendererData() { return s_CurrentRendererData; }

	private:
		static FrameData s_CurrentFrameData;
		static RendererData s_CurrentRendererData;
	};
}