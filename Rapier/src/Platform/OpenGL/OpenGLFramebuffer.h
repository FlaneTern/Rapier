#pragma once

#include "Renderer/Framebuffer.h"

namespace Rapier {
	
	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

		virtual void Resize(uint32_t width, uint32_t height);

	private:
		uint32_t m_RendererId = 0;
		FramebufferSpecification m_Specification;

		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
	};
}