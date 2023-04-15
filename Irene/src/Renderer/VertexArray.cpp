#include "ipch.h"
#include "VertexArray.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace IRENE {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       IRENE_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return new OpenGLVertexArray();
		}

		IRENE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
