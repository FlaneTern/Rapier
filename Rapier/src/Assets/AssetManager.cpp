#include "ipch.h"
#include "Renderer/Renderer.h"
#include "Assets/AssetManager.h"
#include "FileSystem/FileSystem.h"

#include "Assets/Shader/Shader.h"
#include "Assets/Texture/Texture.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Rapier {



	std::unordered_map<std::string, Ref<Texture2D>> AssetManager::s_Textures2D;

	static std::unordered_map<std::string, Ref<Shader>> l_Shaders;
	static std::unordered_map<std::string, Ref<VertexArray>> l_VertexArrays;

	static uint32_t l_ShaderId = 0;
	static uint32_t l_Texture2DId = 0;
	static uint32_t l_VertexArrayId = 0;

	Ref<Shader> AssetManager::LoadShader(const std::string& filename) {
		auto exists = IsShaderLoaded(filename);
		if (exists)
			return exists;

		Ref<Shader> shader;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  shader = nullptr;
		case RendererAPI::API::OpenGL:     shader =  std::make_shared<OpenGLShader>(filename);
		}
		
		shader->SetAssetManagerId(l_ShaderId);
		l_Shaders.insert({ filename, shader });

		l_ShaderId++;

		return shader;
	}


	Ref<Texture2D> AssetManager::LoadTexture2D(const std::string& filename) {
		auto exists = IsTexture2DLoaded(filename);
		if (exists)
			return exists;
		
		Ref<Texture2D> texture2D;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  texture2D = nullptr;
		case RendererAPI::API::OpenGL:     texture2D = std::make_shared<OpenGLTexture2D>(filename);
		}

		texture2D->SetAssetManagerId(l_Texture2DId);
		s_Textures2D.insert({ filename , texture2D });
		l_Texture2DId++;

		return texture2D;
	}



	void AssetManager::Init() {
		CreateVertexArrays();
		LoadAllShaders();
		LoadAllTexture2Ds();
	}

	void AssetManager::CreateVertexArrays() {
		CreateVertexArrayQuad();
		CreateVertexArrayTexture();
	}

	void AssetManager::LoadAllShaders() {
		for (const auto& entry : FileSystem::s_ShaderDirectoryEntries) {
			if (FileSystem::IsShader(entry) && !IsShaderLoaded(entry)) {
				LoadShader(entry);
			}
		}
	}

	void AssetManager::LoadAllTexture2Ds() {
		for (const auto& entry : FileSystem::s_TextureDirectoryEntries) {
			if (FileSystem::IsTexture(entry) && !IsTexture2DLoaded(entry))
				LoadTexture2D(entry);
		}
	}


	Ref<Shader> AssetManager::IsShaderLoaded(const std::string& filename) {
		auto exists = l_Shaders.find(filename);
		if (exists != l_Shaders.end()) {
			return exists->second;
		}

		return nullptr;
	}

	Ref<Texture2D> AssetManager::IsTexture2DLoaded(const std::string& filename) {
		auto exists = s_Textures2D.find(filename);
		if (exists != s_Textures2D.end()) {
			return exists->second;
		}

		return nullptr;
	}

	void AssetManager::CreateVertexArrayQuad() {
		Ref<VertexArray> va = VertexArray::Create();

		float QuadVertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		Ref<VertexBuffer> vb = VertexBuffer::Create(QuadVertices, sizeof(QuadVertices));
		vb->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});

		uint32_t QuadIndices[] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> ib = IndexBuffer::Create(QuadIndices, sizeof(QuadIndices) / sizeof(uint32_t));

		va->AddVertexBuffer(vb);
		va->SetIndexBuffer(ib);

		l_VertexArrays.insert({ "Quad", va });
		l_VertexArrayId++;
	}


	void AssetManager::CreateVertexArrayTexture() {
		Ref<VertexArray> va = VertexArray::Create();
		va->Bind();

		float vertices[] = {
			-0.5, -0.5, 0.0, 0.0, 0.0,
			 0.5, -0.5, 0.0, 1.0, 0.0,
			 0.5,  0.5, 0.0, 1.0, 1.0,
			-0.5,  0.5, 0.0, 0.0, 1.0
		};

		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0
		};

		Ref<VertexBuffer> vb;
		vb = VertexBuffer::Create(vertices, sizeof(vertices));

		vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TextureCoord" }
		});

		Ref<IndexBuffer> ib;
		ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));


		va->AddVertexBuffer(vb);
		va->SetIndexBuffer(ib);

		l_VertexArrays.insert({ "Texture", va });
		l_VertexArrayId++;
	}


	Ref<Shader> AssetManager::GetShader(const std::string& filename) {
		auto exists = l_Shaders.find(filename);
		if (exists != l_Shaders.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Shader with filename :'{0}' doesn't exist!", filename);
		return nullptr;
	}


	Ref<Texture2D> AssetManager::GetTexture2D(const std::string& filename) {
		auto exists = s_Textures2D.find(filename);
		if (exists != s_Textures2D.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Texture with filename :'{0}' doesn't exist!", filename);
		return nullptr;
	}



	Ref<VertexArray> AssetManager::GetVertexArray(const std::string& filename) {
		auto exists = l_VertexArrays.find(filename);
		if (exists != l_VertexArrays.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Texture with filename :'{0}' doesn't exist!", filename);
		return nullptr;
	}

	/*
	Ref<Shader> AssetManager::GetShader(uint32_t id) {
		for (auto& entry : l_Shaders) {
			if (entry.second->GetAssetManagerId() == id) {
				return entry.second;
			}
		}

		RAPIER_CORE_INFO("Shader with id :'{0}' doesn't exist!", id);
		return nullptr;
	}
	Ref<Texture2D> AssetManager::GetTexture2D(uint32_t id){
		for (auto& entry : s_Textures2D) {
			if (entry.second->GetAssetManagerId() == id) {
				return entry.second;
			}
		}

		RAPIER_CORE_INFO("Texture with id :'{0}' doesn't exist!", id);
		return nullptr;
	}
	Ref<VertexArray> AssetManager::GetVertexArray(uint32_t id) {
		for (auto& entry : l_VertexArrays) {
			if (entry.second->GetAssetManagerId() == id) {
				return entry.second;
			}
		}

		RAPIER_CORE_INFO("Texture with id :'{0}' doesn't exist!", id);
		return nullptr;
	}
	*/

	std::vector<Ref<Texture2D>> AssetManager::GetAllTexture2D() {
		std::vector<Ref<Texture2D>> textures;
		textures.reserve(s_Textures2D.size());

		for (const auto& textureEntry : s_Textures2D) {
			textures.push_back(textureEntry.second);
		}

		return textures;
	}


}