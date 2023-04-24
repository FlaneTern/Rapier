#include "ipch.h"
#include "Buffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Rapier {

	////////////////////////////////////////////////////////////////////////
	// Should buffer creation go through asset manager? ////////////////////
	////////////////////////////////////////////////////////////////////////

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		RAPIER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return std::make_shared<OpenGLVertexBuffer>(size);
		}

		RAPIER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		RAPIER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
