#pragma once


namespace Rapier {
	
	struct FramebufferSpecification {
		uint32_t Width, Height;

		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};


	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

		virtual uint32_t GetColorAttachmentRendererId() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};


}