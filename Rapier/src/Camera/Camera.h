#pragma once
#include "glm/glm.hpp"


namespace Rapier {

	class OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		static OrthographicCamera& GetCamera() { return *s_OrthographicCamera; };

		void Set(const glm::vec3& position, float rotation);


		void Update(const glm::vec3& positionOffset, float rotationOffset);

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline float GetRotation() { return m_Rotation; }


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

		static std::unique_ptr<OrthographicCamera> s_OrthographicCamera;
	};
}