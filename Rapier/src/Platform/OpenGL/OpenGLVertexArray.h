#pragma once

#include "ipch.h"
#include "Renderer/VertexArray.h"

namespace Rapier 
{
	class OpenGLVertexArray : public VertexArray 
	{

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		RendererId m_RendererId;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}