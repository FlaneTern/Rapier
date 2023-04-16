#pragma once
#include "ipch.h"
#include "glm/glm.hpp"

namespace IRENE {
	class Shader {
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

	protected:
		uint32_t m_RendererId;
	};
}