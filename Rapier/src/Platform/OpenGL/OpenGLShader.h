#pragma once

#include "glm/glm.hpp"
#include "Assets/Shader/Shader.h"

namespace Rapier{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filename);
		~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformInt(const std::string& name, int value) override;
		virtual void UploadUniformFloat4(const std::string& name, glm::vec4 value) override;
	};
}