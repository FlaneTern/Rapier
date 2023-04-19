#include "ipch.h"
#include "Renderer/Renderer.h"
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

	std::map<AssetManager::DefaultShaderId, Ref<Shader>> AssetManager::s_DefaultShaders;
	std::map<AssetManager::DefaultTexture2DId, Ref<Texture2D>> AssetManager::s_DefaultTextures2D;
	std::map<AssetManager::DefaultVertexArrayId, Ref<VertexArray>> AssetManager::s_DefaultVertexArrays;



	/// <summary>
	/// Checks for the list of saved shaders. If the shader already exists returns it, else creates the shader and returns it.
	/// </summary>
	/// <param name="vertexName">: Filepath to the vertex shader</param>
	/// <param name="fragmentName">: Filepath to the vertex shader</param>
	/// <returns>The loaded shader</returns>
	Ref<Shader> AssetManager::LoadShader(const std::string& vertexName, const std::string& fragmentName) {
		auto exists = s_Shaders.find(vertexName + fragmentName);
		if (exists != s_Shaders.end()) {
			RAPIER_CORE_INFO("Shader with filename :'{0}' was already created!", vertexName + fragmentName);
			return exists->second;
		}

		Ref<Shader> shader;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  shader = nullptr;
		case RendererAPI::API::OpenGL:     shader =  std::make_shared<OpenGLShader>(vertexName, fragmentName);
		}
		
		shader->SetAssetManagerId(s_ShaderId);
		s_Shaders.insert({ { s_ShaderId, vertexName + fragmentName }, shader });
		s_ShaderId++;

		return shader;
	}


	/// <summary>
	/// Checks for the list of saved textures. If the shader already exists returns it, else creates the texture and returns it.
	/// </summary>
	/// <param name="filename">: Filepath to the texture</param>
	/// <returns>The loaded texture</returns>
	Ref<Texture2D> AssetManager::LoadTexture2D(const std::string& filename) {
		auto exists = s_Textures2D.find(filename);
		if (exists != s_Textures2D.end()) {
			RAPIER_CORE_INFO("Texture with filename :'{0}' was already created!", filename);
			return exists->second;
		}

		Ref<Texture2D> texture2D;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  texture2D = nullptr;
		case RendererAPI::API::OpenGL:     texture2D = std::make_shared<OpenGLTexture2D>(filename);
		}

		texture2D->SetAssetManagerId(s_Texture2DId);
		s_Textures2D.insert({ { s_Texture2DId, filename }, texture2D });
		s_Texture2DId++;

		return texture2D;
	}



	void AssetManager::Init() {
		CreateVertexArrays();
		LoadDefaultShaders();
		LoadDefaultTexture2Ds();
	}

	void AssetManager::CreateVertexArrays() {
		CreateVertexArrayQuad();
		CreateVertexArrayTexture();
	}

	void AssetManager::LoadDefaultShaders() {
		LoadDefaultShader("GradientVertex.rshader", "GradientFragment.rshader", DefaultShaderId::GradientColorShader);
		LoadDefaultShader("TextureVertex.rshader", "TextureFragment.rshader", DefaultShaderId::TextureShader);
	}

	void AssetManager::LoadDefaultTexture2Ds() {
		LoadDefaultTexture2D("irene-gyatekora.png", DefaultTexture2DId::IreneGyatekora);
		LoadDefaultTexture2D("irene-gyatekora-v0.png", DefaultTexture2DId::IreneGyatekora2);
		LoadDefaultTexture2D("irene-gyatekora-v1.png", DefaultTexture2DId::IreneGyatekora3);
	}




	void AssetManager::CreateVertexArrayQuad() {
		Ref<VertexArray> va = VertexArray::Create();

		float QuadVertices[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
		};

		Ref<VertexBuffer> vb = VertexBuffer::Create(QuadVertices, sizeof(QuadVertices));
		vb->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});

		uint32_t QuadIndices[] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> ib = IndexBuffer::Create(QuadIndices, sizeof(QuadIndices) / sizeof(uint32_t));

		va->AddVertexBuffer(vb);
		va->SetIndexBuffer(ib);

		s_DefaultVertexArrays.insert({DefaultVertexArrayId::Quad, va});
	}


	void AssetManager::CreateVertexArrayTexture() {
		Ref<VertexArray> va = VertexArray::Create();
		va->Bind();

		float vertices[] = {
			-1.0, -1.0, 0.0, 0.0, 0.0,
			 1.0, -1.0, 0.0, 1.0, 0.0,
			 1.0,  1.0, 0.0, 1.0, 1.0,
			-1.0,  1.0, 0.0, 0.0, 1.0
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

		s_DefaultVertexArrays.insert({ DefaultVertexArrayId::Texture, va });
	}

	void AssetManager::LoadDefaultShader(const std::string& vertexName, const std::string& fragmentName, DefaultShaderId id) {
		Ref<Shader> shader;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  shader = nullptr;
		case RendererAPI::API::OpenGL:     shader = std::make_shared<OpenGLShader>(vertexName, fragmentName);
		}

		shader->SetAssetManagerId((uint32_t)id);
		s_DefaultShaders.insert({ id, shader });


		// temp !!!!! //////////////////////////////
		// temp !!!!! //////////////////////////////
		// temp !!!!! //////////////////////////////
		if (id == DefaultShaderId::TextureShader) {
			shader->Bind();
			shader->UploadUniformInt("u_Texture", 0);
		}
	}


	void AssetManager::LoadDefaultTexture2D(const std::string& filename, DefaultTexture2DId id) {
		Ref<Texture2D> texture2D;
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:       RAPIER_CORE_ASSERT(false, "RendererAPI::None is not supported!");  texture2D = nullptr;
		case RendererAPI::API::OpenGL:     texture2D = std::make_shared<OpenGLTexture2D>(filename);
		}

		texture2D->SetAssetManagerId((uint32_t)id);
		s_DefaultTextures2D.insert({ id, texture2D });
	}





	Ref<Shader> AssetManager::GetShader(const std::string& filename) {
		auto exists = s_Shaders.find(filename);
		if (exists != s_Shaders.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Shader with filename :'{0}' doesn't exist!", filename);
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

	Ref<Texture2D> AssetManager::GetTexture2D(const std::string& filename) {
		auto exists = s_Textures2D.find(filename);
		if (exists != s_Textures2D.end()) {
			return exists->second;
		}

		RAPIER_CORE_INFO("Texture with filename :'{0}' doesn't exist!", filename);
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