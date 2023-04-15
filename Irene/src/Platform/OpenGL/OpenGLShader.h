#pragma once

#include "Renderer/Shader.h"

namespace IRENE{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;
	};
}