#include "ipch.h"
#include "VertexArray.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rapier {

	////////////////////////////////////////////////////////////////////////
	// Should vertexarray creation go through asset manager? ///////////////
	////////////////////////////////////////////////////////////////////////

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return std::make_shared<OpenGLVertexArray>();
		}

		RAPIER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
