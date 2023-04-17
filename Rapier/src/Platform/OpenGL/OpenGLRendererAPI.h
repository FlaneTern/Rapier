#pragma once

#include "Renderer/RendererAPI.h"

namespace Rapier {
	class OpenGLRendererAPI : public RendererAPI {
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}