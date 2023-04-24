#pragma once

#include "Renderer/RendererAPI.h"


namespace Rapier {
	class RenderCommand {
	public:

		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }


		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) 
			{ s_RendererAPI->DrawIndexed(vertexArray); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}