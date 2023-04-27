#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Rapier {

	class Camera {
	public:
		Camera() = default;

		Camera(const glm::mat4& cam)
			: m_ProjectionMatrix(cam) {}

		Camera(float left, float right, float bottom, float top, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);


		void CalculateProjection();

		float GetSize() const { return m_Size; }
		void SetSize(float size) { m_Size = size; CalculateProjection(); }


		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }

	private:
		float m_AspectRatio = 16.0f / 9.0f, m_Size = 2.0f;
		float m_FarClip = 1000.0f, m_NearClip = -1000.0f;
		glm::mat4 m_ProjectionMatrix = glm::ortho(-m_Size * m_AspectRatio * 0.5f, m_Size * m_AspectRatio * 0.5f,
			-m_Size * 0.5f, m_Size * 0.5f, m_NearClip, m_FarClip);

		uint32_t m_Height = 768;
	};

}