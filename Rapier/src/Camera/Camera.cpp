#include "ipch.h"
#include "Camera/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Rapier {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void OrthographicCamera::CalculateViewProjectionMatrix() {
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	

	Camera::Camera(float left, float right, float bottom, float top, float farClip, float nearClip)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, farClip, nearClip))
	{
		m_Size = top - bottom;
		m_AspectRatio = (right - left) / m_Size;
	}

	void Camera::SetViewportSize(uint32_t width, uint32_t height) {
		m_AspectRatio = (float)width / (float)height;

		CalculateProjection();
	}

	void Camera::CalculateProjection() {
		float left = -m_Size * m_AspectRatio * 0.5f;
		float right = m_Size * m_AspectRatio * 0.5f;
		float bottom = -m_Size * 0.5f;
		float top =  m_Size * 0.5f;

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_NearClip, m_FarClip);
	}
}