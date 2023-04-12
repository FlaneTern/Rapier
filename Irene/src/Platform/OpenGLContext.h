#pragma once

#include "Renderer/RendererContext.h"

struct GLFWwindow;

namespace IRENE {
	class OpenGLContext : public RendererContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}