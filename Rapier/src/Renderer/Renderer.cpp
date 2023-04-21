#include "ipch.h"
#include "Renderer.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"


#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	std::unique_ptr<Renderer> Renderer::s_Renderer = nullptr;

	void Renderer::Create() {
		RAPIER_CORE_ASSERT(!s_Renderer, "Renderer already exists!");

		Renderer::s_Renderer.reset(new Renderer());
	}

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		RAPIER_CORE_ASSERT(!s_Renderer->m_StartedScene, "Scene has already started!");
		s_Renderer->m_StartedScene = true;
		s_Renderer->m_SceneData.reset(new SceneData(camera));
	}

	void Renderer::EndScene() {
		s_Renderer->m_StartedScene = false;
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	Renderer::Renderer()
		:m_StartedScene(false) {}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	std::unique_ptr<Renderer2D> Renderer2D::s_Renderer2D = nullptr;

	void Renderer2D::Create() {
		RAPIER_CORE_ASSERT(!s_Renderer2D, "Renderer already exists!");

		Renderer2D::s_Renderer2D.reset(new Renderer2D());
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		RAPIER_CORE_ASSERT(!s_Renderer2D->m_StartedScene, "Scene has already started!");
		s_Renderer2D->m_StartedScene = true;
		s_Renderer2D->m_SceneData.reset(new SceneData(camera));
	}

	void Renderer2D::BeginScene(const glm::mat4& camera) {
		RAPIER_CORE_ASSERT(!s_Renderer2D->m_StartedScene, "Scene has already started!");
		s_Renderer2D->m_StartedScene = true;
		s_Renderer2D->m_SceneData.reset(new SceneData(camera));
	}

	void Renderer2D::EndScene() {
		s_Renderer2D->m_StartedScene = false;
	}

	void Renderer2D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer2D->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	Renderer2D::Renderer2D()
		:m_StartedScene(false) {}





	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation) {
		DrawQuad(glm::vec3(position, 1.0f), size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, float size, const glm::vec4& color, float rotation) {
		DrawQuad(position, glm::vec2(size, size), color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, float size, const glm::vec4& color, float rotation) {
		DrawQuad(glm::vec3(position, 1.0f), glm::vec2(size, size), color, rotation);
	}


	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
		Ref<Shader> shader = AssetManager::GetDefaultShader(AssetManager::DefaultShaderId::GradientColorShader);
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer2D->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat4("u_Color", color);

		Ref<VertexArray> va = AssetManager::GetDefaultVertexArray(AssetManager::DefaultVertexArrayId::Quad);
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}




	void Renderer2D::DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture) {
		texture->Bind();
		Ref<Shader> shader = AssetManager::GetDefaultShader(AssetManager::DefaultShaderId::TextureShader);
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer2D->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		Ref<VertexArray> va = AssetManager::GetDefaultVertexArray(AssetManager::DefaultVertexArrayId::Texture);
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

	void Renderer2D::DrawTexture(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float rotation) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawTexture(transform, texture);
	}

	void Renderer2D::DrawTexture(const glm::vec3& position, const glm::vec2& size, AssetManager::DefaultTexture2DId id, float rotation) {
		DrawTexture(position, size, AssetManager::GetDefaultTexture2D(id), rotation);
	}



	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color) {
		Ref<Shader> shader = AssetManager::GetDefaultShader(AssetManager::DefaultShaderId::SolidCircleShader);
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer2D->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat4("u_Color", color);

		Ref<VertexArray> va = AssetManager::GetDefaultVertexArray(AssetManager::DefaultVertexArrayId::Quad);
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

	void Renderer2D::DrawCircle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		DrawCircle(transform, color);
	}

}