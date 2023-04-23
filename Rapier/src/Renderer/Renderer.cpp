#include "ipch.h"
#include "Renderer.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"


#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	static Scope<SceneData> l_SceneData;
	bool l_StartedScene = false;


	void Renderer::EndScene() {
		l_StartedScene = false;
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	static Scope<SceneData> l_SceneData2D;
	bool l_StartedScene2D = false;


	void Renderer2D::BeginScene(const glm::mat4& camera) {
		RAPIER_CORE_ASSERT(!l_StartedScene2D, "Scene has already started!");
		l_StartedScene2D = true;
		l_SceneData2D.reset(new SceneData(camera));
	}

	void Renderer2D::EndScene() {
		l_StartedScene2D = false;
	}

	void Renderer2D::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


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
		Ref<Shader> shader = AssetManager::GetShader("GradientQuad.rshader");
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat4("u_Color", color);

		Ref<VertexArray> va = AssetManager::GetVertexArray("Quad");
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}


	void Renderer2D::DrawTexture(const glm::mat4& transform, Ref<Texture2D> texture) {
		texture->Bind();
		Ref<Shader> shader = AssetManager::GetShader("Texture.rshader");
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		Ref<VertexArray> va = AssetManager::GetVertexArray("Texture");
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

	void Renderer2D::DrawTexture(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float rotation) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawTexture(transform, texture);
	}


	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color) {
		Ref<Shader> shader = AssetManager::GetShader("SolidCircle.rshader");
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", l_SceneData2D->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		shader->UploadUniformFloat4("u_Color", color);

		Ref<VertexArray> va = AssetManager::GetVertexArray("Quad");
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}

	void Renderer2D::DrawCircle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		DrawCircle(transform, color);
	}

}