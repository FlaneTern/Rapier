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

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual RendererId GetColorAttachmentRendererId(uint32_t attachmentIndex) const override { return m_ColorAttachments[attachmentIndex]; }
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

		virtual void Resize(uint32_t width, uint32_t height);

	private:
		RendererId m_RendererId = 0;
		FramebufferSpecification m_Specification;


		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification;

		std::vector<RendererId> m_ColorAttachments;
		RendererId m_DepthAttachment = 0;
	};
}