#pragma once


namespace Rapier 
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Color = RGBA8,
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};
	
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		std::vector<FramebufferTextureSpecification> Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};


	class RAPIER_API Framebuffer 
	{
	public:
		virtual ~Framebuffer() = default;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

		virtual RendererId GetColorAttachmentRendererId(uint32_t AttachmentIndex) const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	};


}