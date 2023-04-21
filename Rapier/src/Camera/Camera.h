#pragma once
#include "glm/glm.hpp"


namespace Rapier {

	class Camera {
	public:
		Camera() = default;

		Camera(const glm::mat4& cam)
			: m_ProjectionMatrix(cam) {} // !!!!!!! set left, right, ...

		Camera(float left, float right, float bottom, float top, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		void CalculateProjection();

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

		float m_AspectRatio = 16.0f / 9.0f, m_Size = 2.0f;
		float m_FarClip = 1.0f, m_NearClip = -1.0f;
	};

	class OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(glm::vec3 position) { m_Position = position; CalculateViewProjectionMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewProjectionMatrix(); }

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:

		void CalculateViewProjectionMatrix();

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}