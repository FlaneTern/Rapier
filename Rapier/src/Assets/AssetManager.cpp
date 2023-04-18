#include "ipch.h"
#include "Assets/AssetManager.h"
#include "FileSystem/FileSystem.h"

#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Rapier {

	uint32_t AssetManager::s_ShaderId = 0;
	uint32_t AssetManager::s_Texture2DId = 0;

	std::map<AssetIdentifier, Ref<Shader>, CompareAssetIdentifier> AssetManager::s_Shaders;
	std::map<AssetIdentifier, Ref<Texture2D>, CompareAssetIdentifier> AssetManager::s_Textures2D;


	/// <summary>
	/// Checks for the list of saved shaders. If the shader already exists returns it, else creates the shader and returns it.
	/// </summary>
	/// <param name="vertexPath">: Filepath to the vertex shader</param>
	/// <param name="fragmentPath">: Filepath to the vertex shader</param>
	/// <returns>The loaded shader</returns>
	Ref<Shader> AssetManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath) {
		auto exists = s_Shaders.find(vertexPath + fragmentPath);
		if (exists != s_Shaders.end()) {
			RAPIER_CORE_INFO("Shader at filepath :'{0}' was already created!", vertexPath + fragmentPath);
			return exists->second;
		}

		Ref<Shader> shader;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  shader = nullptr;
		case RendererAPI::API::OpenGL:     shader =  std::make_shared<OpenGLShader>(vertexPath, fragmentPath);
		}
		
		shader->SetAssetManagerId(s_ShaderId);
		s_Shaders.insert({ { s_ShaderId, vertexPath + fragmentPath }, shader });
		s_ShaderId++;

		return shader;
	}


	/// <summary>
	/// Checks for the list of saved textures. If the shader already exists returns it, else creates the texture and returns it.
	/// </summary>
	/// <param name="filepath">: Filepath to the texture</param>
	/// <returns>The loaded texture</returns>
	Ref<Texture2D> AssetManager::LoadTexture2D(const std::string& filepath) {
		auto exists = s_Textures2D.find(filepath);
		if (exists != s_Textures2D.end()) {
			RAPIER_CORE_INFO("Texture at filepath :'{0}' was already created!", filepath);
			return exists->second;
		}

		Ref<Texture2D> texture2D;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  texture2D = nullptr;
		case RendererAPI::API::OpenGL:     texture2D = std::make_shared<OpenGLTexture2D>(filepath);
		}

		texture2D->SetAssetManagerId(s_Texture2DId);
		s_Textures2D.insert({ { s_Texture2DId, filepath }, texture2D });
		s_Texture2DId++;

		return texture2D;
	}



	Ref<Shader> AssetManager::GetShader(const std::string& filepath) {
		auto exists = s_Shaders.find(filepath);
		if (exists != s_Shaders.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Shader at filepath :'{0}' doesn't exist!", filepath);
		return nullptr;
	}

	Ref<Shader> AssetManager::GetShader(uint32_t id) {
		auto exists = s_Shaders.find(id);
		if (exists != s_Shaders.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Shader with id :'{0}' doesn't exist!", id);
		return nullptr;
	}

	Ref<Texture2D> AssetManager::GetTexture2D(const std::string& filepath) {
		auto exists = s_Textures2D.find(filepath);
		if (exists != s_Textures2D.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Texture at filepath :'{0}' doesn't exist!", filepath);
		return nullptr;
	}

	Ref<Texture2D> AssetManager::GetTexture2D(uint32_t id){
		auto exists = s_Textures2D.find(id);
		if (exists != s_Textures2D.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Texture with id :'{0}' doesn't exist!", id);
		return nullptr;
	}

}