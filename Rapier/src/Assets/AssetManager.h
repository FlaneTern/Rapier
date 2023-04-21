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





	// Default assets
	public:
		enum class DefaultShaderId {
			GradientColorShader = 0,
			TextureShader,
			SolidCircleShader
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


		static Ref<Shader> GetDefaultShader(DefaultShaderId id);
		static Ref<Texture2D> GetDefaultTexture2D(DefaultTexture2DId id);
		static Ref<VertexArray> GetDefaultVertexArray(DefaultVertexArrayId id);

	private:
		friend class Renderer2D;



		static void LoadDefaultShaders();
		static void LoadDefaultTexture2Ds();
		static void CreateVertexArrays();
		static void LoadDefaultShader(const std::string& vertexName, const std::string& fragmentName, DefaultShaderId id);
		static void LoadDefaultTexture2D(const std::string& filename, DefaultTexture2DId id);





		static void CreateVertexArrayQuad();
		static void CreateVertexArrayTexture();

	};



	
	

}