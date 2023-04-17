#include "ipch.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rapier {
	Shader* Shader::Create(const std::string& vertex, const std::string& fragment) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:     return new OpenGLShader(vertex, fragment);
		}

		RAPIER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}