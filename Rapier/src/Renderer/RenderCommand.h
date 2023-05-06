#pragma once

#include "Renderer/RendererAPI.h"


namespace Rapier 
{

	class RAPIER_API RenderCommand 
	{
	public:

		inline static void SetClearColor(const glm::vec4& color) 
		{ 
			s_RendererAPI->SetClearColor(color); 
		}

		inline static void Clear(uint8_t bufferMask = (RapierColorBufferBit | RapierDepthBufferBit)) 
		{ 
			s_RendererAPI->Clear(bufferMask);
		}

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

		inline static void SetDepthFunction(DepthFunction depthfunction)
		{
			s_RendererAPI->SetDepthFunction(depthfunction);
		}

		inline static DepthFunction GetDepthFunction()
		{
			return s_RendererAPI->GetDepthFunction();
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}