#include "ipch.h"
#include "Camera/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace IRENE {

	std::unique_ptr<OrthographicCamera> OrthographicCamera::s_OrthographicCamera = std::make_unique<OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}



	void OrthographicCamera::Update(const glm::vec3& positionOffset, float rotationOffset) {
		m_Position += positionOffset;
		m_Rotation += rotationOffset;
		CalculateViewProjectionMatrix();
	}



	void OrthographicCamera::Set(const glm::vec3& position, float rotation) {
		m_Position = position; 
		m_Rotation = rotation;
		CalculateViewProjectionMatrix(); 
	}


	void OrthographicCamera::CalculateViewProjectionMatrix() {
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
}