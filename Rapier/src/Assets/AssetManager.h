#pragma once

#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

namespace Rapier {

	struct AssetIdentifier {
		uint32_t Id;
		std::string Filename;
	};


	struct CompareAssetIdentifier
	{
		using is_transparent = std::true_type;

		bool operator()(const AssetIdentifier& lhs, const AssetIdentifier& rhs) const { return lhs.Id < rhs.Id; }
		bool operator()(const AssetIdentifier& lhs, const std::string& rhs) const { return lhs.Filename < rhs; }
		bool operator()(const std::string& lhs, const AssetIdentifier& rhs) const { return lhs < rhs.Filename; }
		bool operator()(const AssetIdentifier& lhs, uint32_t rhs) const { return lhs.Id < rhs; }
		bool operator()(uint32_t lhs, const AssetIdentifier& rhs) const { return lhs < rhs.Id; }
	};


	class AssetManager {

	public:
		static void Init();




		static Ref<Shader> LoadShader(const std::string& vertexName, const std::string& fragmentName);
		static Ref<Texture2D> LoadTexture2D(const std::string& filename);


		static Ref<Shader> GetShader(const std::string& filename);
		static Ref<Shader> GetShader(uint32_t id);
		static Ref<Texture2D> GetTexture2D(const std::string& filename);
		static Ref<Texture2D> GetTexture2D(uint32_t id);

	private:

		static std::map<AssetIdentifier, Ref<Shader>, CompareAssetIdentifier> s_Shaders;
		static std::map<AssetIdentifier, Ref<Texture2D>, CompareAssetIdentifier> s_Textures2D;

		static uint32_t s_ShaderId;
		static uint32_t s_Texture2DId;



	// Default assets
	public:
		enum class DefaultShaderId {
			GradientColorShader = 0,
			TextureShader
		};

		enum class DefaultTexture2DId {
			IreneGyatekora = 0,
			IreneGyatekora2,
			IreneGyatekora3
		};

		enum class DefaultVertexArrayId {
			Quad = 0,
			Texture
		};


	private:
		friend class Renderer2D;

		static Ref<Shader> GetDefaultShader(DefaultShaderId id) { return s_DefaultShaders[id]; }
		static Ref<Texture2D> GetDefaultTexture2D(DefaultTexture2DId id) { return s_DefaultTextures2D[id]; }
		static Ref<VertexArray> GetDefaultVertexArray(DefaultVertexArrayId id) { return s_DefaultVertexArrays[id]; }



		static void LoadDefaultShaders();
		static void LoadDefaultTexture2Ds();
		static void CreateVertexArrays();
		static void LoadDefaultShader(const std::string& vertexName, const std::string& fragmentName, DefaultShaderId id);
		static void LoadDefaultTexture2D(const std::string& filename, DefaultTexture2DId id);


		static std::map<DefaultShaderId, Ref<Shader>> s_DefaultShaders;
		static std::map<DefaultTexture2DId, Ref<Texture2D>> s_DefaultTextures2D;
		static std::map<DefaultVertexArrayId, Ref<VertexArray>> s_DefaultVertexArrays;


		static void CreateVertexArrayQuad();
		static void CreateVertexArrayTexture();

	};



	
	

}