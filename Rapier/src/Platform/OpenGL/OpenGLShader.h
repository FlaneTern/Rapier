#pragma once

#include "glm/glm.hpp"
#include "Renderer/Shader.h"

namespace Rapier{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	};
}