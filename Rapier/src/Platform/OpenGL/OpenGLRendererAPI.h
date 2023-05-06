#pragma once

#include "Renderer/RendererAPI.h"

namespace Rapier 
{
	class OpenGLRendererAPI : public RendererAPI 
	{
		virtual void Clear(uint8_t bufferMask) override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;

		virtual void SetLineWidth(float width) override;

		virtual void SetDepthFunction(DepthFunction depthfunction) override;
		virtual DepthFunction GetDepthFunction() override;

		virtual void Init() override;
	};
}