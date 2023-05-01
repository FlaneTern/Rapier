#include "ipch.h"
#include "Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Rapier {

	// temp/////////////////
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:     return GL_FLOAT;
		case ShaderDataType::Float2:    return GL_FLOAT;
		case ShaderDataType::Float3:    return GL_FLOAT;
		case ShaderDataType::Float4:    return GL_FLOAT;
		case ShaderDataType::Mat3:      return GL_FLOAT;
		case ShaderDataType::Mat4:      return GL_FLOAT;
		case ShaderDataType::Int:       return GL_INT;
		case ShaderDataType::Int2:      return GL_INT;
		case ShaderDataType::Int3:      return GL_INT;
		case ShaderDataType::Int4:      return GL_INT;
		}

		RAPIER_CORE_ASSERT(false, "Unknown ShaderDataType in ShaderDataTypeToOpenGLType()");
		return 0;
	}



	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererId);
	}


	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(m_RendererId);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			switch (element.Type) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset
				);

				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(index);
				glVertexAttribIPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset
				);

				break;
			}
			}

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererId);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}
}