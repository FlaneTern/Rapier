#include "ipch.h"
#include "Camera/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Rapier 
{

	Camera::Camera(float aspectRatio, float size, float farClip, float nearClip, uint32_t height)
		: m_AspectRatio(aspectRatio), m_Size(size), m_FarClip(farClip), m_NearClip(nearClip), m_Height(height) 
	{
		CalculateProjection();
	}

	Camera::Camera(float left, float right, float bottom, float top, float farClip, float nearClip)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, farClip, nearClip))
	{
		m_Height = 768;
		m_Size = top - bottom;
		m_AspectRatio = (right - left) / m_Size;
	}

	void Camera::SetViewportSize(uint32_t width, uint32_t height) 
	{
		m_Size *= (float)height / (float)m_Height;
		m_Height = height;
		m_AspectRatio = (float)width / (float)height;

		CalculateProjection();
	}



	void Camera::CalculateProjection() 
	{
		float left = -m_Size * m_AspectRatio * 0.5f;
		float right = m_Size * m_AspectRatio * 0.5f;
		float bottom = -m_Size * 0.5f;
		float top =  m_Size * 0.5f;

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_NearClip, m_FarClip);
	}

}