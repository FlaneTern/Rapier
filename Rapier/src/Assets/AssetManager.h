#pragma once

#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"
#include "Renderer/VertexArray.h"

namespace Rapier 
{

	class RAPIER_API AssetManager 
	{

	public:
		static void Init();

		static Ref<Shader> LoadShader(const std::string& filename);
		static Ref<Texture2D> LoadTexture2D(const std::string& filename);
		static Ref<Texture2D> GetWhiteTexture();

		static void UnloadAllTexture2Ds();
		static void UnloadAllShaders();


		static Ref<Shader> GetShader(const std::string& filename);
		//static Ref<Shader> GetShader(uint32_t id);
		static Ref<Texture2D> GetTexture2D(const std::string& filename);
		//static Ref<Texture2D> GetTexture2D(uint32_t id);

		static std::vector<Ref<Texture2D>> GetAllTexture2D();


		static Ref<Shader> IsShaderLoaded(const std::string& filename);
		static Ref<Texture2D> IsTexture2DLoaded(const std::string& filename);


	private:
		friend class Renderer2D;
		friend class AssetPanel;

		static void CreateWhiteTexture();
		static void LoadAllShaders();
		static void LoadAllTexture2Ds();

	};



	
	

}