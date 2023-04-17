#pragma once

#include "ipch.h"
#include "Renderer/VertexArray.h"

namespace Rapier {
	class OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererId;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}