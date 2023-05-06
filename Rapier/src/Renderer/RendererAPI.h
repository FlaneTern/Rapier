#pragma once

#include "ipch.h"
#include "glm/glm.hpp"

#include "Renderer/VertexArray.h"

namespace Rapier
{

	enum RenderBufferMask
	{
		RapierColorBufferBit = BIT(0),
		RapierDepthBufferBit = BIT(1),
		RapierStencilBufferBit = BIT(2)
	};

	enum class DepthFunction 
	{
		Never,
		Less,
		Equal,
		LessEqual,
		Greater,
		GreaterEqual,
		NotEqual,
		Always
	};
	
	class RendererAPI
	{
	public:
		enum class API 
		{
			None = 0,
			OpenGL = 1
		};

		virtual void Init() = 0;

		virtual void Clear(uint8_t bufferMask) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

		virtual void SetLineWidth(float width) = 0;

		virtual void SetDepthFunction(DepthFunction depthfunction) = 0;
		virtual DepthFunction GetDepthFunction() = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}