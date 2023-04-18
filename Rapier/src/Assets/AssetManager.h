#pragma once

#include "Renderer/Renderer.h"
#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

namespace Rapier {

	struct AssetIdentifier {
		uint32_t Id;
		std::string Filepath;
	};


	struct CompareAssetIdentifier
	{
		using is_transparent = std::true_type;

		bool operator()(const AssetIdentifier& lhs, const AssetIdentifier& rhs) const { return lhs.Id < rhs.Id; }
		bool operator()(const AssetIdentifier& lhs, const std::string& rhs) const { return lhs.Filepath < rhs; }
		bool operator()(const std::string& lhs, const AssetIdentifier& rhs) const { return lhs < rhs.Filepath; }
		bool operator()(const AssetIdentifier& lhs, uint32_t rhs) const { return lhs.Id < rhs; }
		bool operator()(uint32_t lhs, const AssetIdentifier& rhs) const { return lhs < rhs.Id; }
	};


	class AssetManager {

	public:
		static Ref<Shader> LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
		static Ref<Texture2D> LoadTexture2D(const std::string& filepath);


		static Ref<Shader> GetShader(const std::string& filepath);
		static Ref<Shader> GetShader(uint32_t id);
		static Ref<Texture2D> GetTexture2D(const std::string& filepath);
		static Ref<Texture2D> GetTexture2D(uint32_t id);

	private:
		static std::map<AssetIdentifier, Ref<Shader>, CompareAssetIdentifier> s_Shaders;
		static std::map<AssetIdentifier, Ref<Texture2D>, CompareAssetIdentifier> s_Textures2D;

		static uint32_t s_ShaderId;
		static uint32_t s_Texture2DId;
	};



	
	

}