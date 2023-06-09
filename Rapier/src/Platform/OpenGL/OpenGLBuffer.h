#pragma once

#include "Renderer/Buffer.h"

namespace Rapier 
{
	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();


		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(void* data, uint32_t size) override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		RendererId m_RendererId;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const override { return m_Count; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		RendererId m_RendererId;
		uint32_t m_Count;
	};
}
