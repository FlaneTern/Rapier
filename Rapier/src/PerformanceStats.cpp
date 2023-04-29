#include "ipch.h"

#include "PerformanceStats.h"

namespace Rapier {

	FrameData PerformanceStats::s_CurrentFrameData;
	RendererData PerformanceStats::s_CurrentRendererData;

	void PerformanceStats::BeginFrame() {
		s_CurrentFrameData = FrameData();
		s_CurrentRendererData = RendererData();
	}


	void PerformanceStats::AddFunctionTime(FunctionTimeData data) {
		s_CurrentFrameData.FunctionTime.push_back(data);
	}

	void PerformanceStats::AddQuadCount() {
		s_CurrentRendererData.QuadCount++;
	}

	void PerformanceStats::AddTextureCount() {
		// existing textures get recounted after flush !!!!!!!!!
		s_CurrentRendererData.TextureCount++;
	}

	void PerformanceStats::AddDrawCallCount() {
		s_CurrentRendererData.DrawCallCount++;
	}
}