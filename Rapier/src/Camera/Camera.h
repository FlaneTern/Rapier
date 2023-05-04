#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Rapier {
	class RAPIER_API Camera {
	public:
		Camera() = default;

		Camera(const glm::mat4& cam)
			: m_ProjectionMatrix(cam) {}

		Camera(float left, float right, float bottom, float top, float nearClip, float farClip);

		Camera(float aspectRatio, float size, float farClip, float nearClip, uint32_t height);

		void SetViewportSize(uint32_t width, uint32_t height);

		void CalculateProjection();

		float GetSize() const { return m_Size; }
		float GetAspectRatio() const { return m_AspectRatio; }
		float GetFarClip() const { return m_FarClip; }
		float GetNearClip() const { return m_NearClip; }
		uint32_t GetHeight() const { return m_Height; }

		void SetSize(float size) { m_Size = size; CalculateProjection(); }

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }

	protected:
		float m_AspectRatio = 16.0f / 9.0f, m_Size = 2.0f;
		float m_FarClip = 1000.0f, m_NearClip = -1000.0f;
		uint32_t m_Height = 768;

		glm::mat4 m_ProjectionMatrix = glm::ortho(-m_Size * m_AspectRatio * 0.5f, m_Size * m_AspectRatio * 0.5f,
			-m_Size * 0.5f, m_Size * 0.5f, m_NearClip, m_FarClip);
	};

}