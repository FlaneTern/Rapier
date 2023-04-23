#pragma once

#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

namespace Rapier {

	class AssetManager {

	public:
		static void Init();

		static Ref<Shader> LoadShader(const std::string& filename);
		static Ref<Texture2D> LoadTexture2D(const std::string& filename);


		static Ref<Shader> GetShader(const std::string& filename);
		//static Ref<Shader> GetShader(uint32_t id);
		static Ref<Texture2D> GetTexture2D(const std::string& filename);
		//static Ref<Texture2D> GetTexture2D(uint32_t id);
		static Ref<VertexArray> GetVertexArray(const std::string& filename);
		//static Ref<VertexArray> GetVertexArray(uint32_t id);

		static std::vector<Ref<Texture2D>> GetAllTexture2D();


		// IMPLEMENT BETTER DEFAULT SYSTEM !!!!! //
		// IMPLEMENT BETTER DEFAULT SYSTEM !!!!! //
		// IMPLEMENT BETTER DEFAULT SYSTEM !!!!! //
		// IMPLEMENT BETTER DEFAULT SYSTEM !!!!! //

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




	private:
		friend class Renderer2D;
		friend class AssetPanel;

		static std::map<std::string, Ref<Texture2D>> s_Textures2D;

		static void LoadDefaultShaders();
		static void LoadDefaultTexture2Ds();
		static void CreateVertexArrays();

		static void CreateVertexArrayQuad();
		static void CreateVertexArrayTexture();

	};



	
	

}