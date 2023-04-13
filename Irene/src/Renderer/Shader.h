#pragma once
#include "ipch.h"

namespace IRENE {
	class Shader {
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	protected:
		uint32_t m_RendererId;
	};
}