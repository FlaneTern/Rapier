#include "ipch.h"

#include "Renderer/Framebuffer.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Rapier {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return std::make_shared<OpenGLFramebuffer>(spec);
		}


	}
}