#include "ipch.h"
#include "Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace IRENE {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}