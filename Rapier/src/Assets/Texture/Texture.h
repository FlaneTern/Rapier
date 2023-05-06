#pragma once

namespace Rapier 
{
	
	class RAPIER_API Texture 
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t GetAssetManagerId() const = 0;
		virtual void SetAssetManagerId(uint32_t id) = 0;

		virtual uint32_t GetRendererId() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual const std::string& GetFilepath() const = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& filename);
		static Ref<Texture2D> CreateWhiteTexture();
	};
}