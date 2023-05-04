#pragma once

#include "Renderer/RendererAPI.h"


namespace Rapier {
	class RAPIER_API RenderCommand {
	public:

		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }


		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{ 
			s_RendererAPI->DrawIndexed(vertexArray); 
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
		{
			s_RendererAPI->DrawLines(vertexArray, vertexCount);
		}

		inline static void SetLineWidth(float width)
		{
			s_RendererAPI->SetLineWidth(width);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}