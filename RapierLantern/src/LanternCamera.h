#pragma once

#include "Rapier.h"

#include "glm/glm.hpp"

namespace Rapier 
{
	class LanternLayer;

	class LanternCamera : public Camera
	{
	public:
		LanternCamera();

		void CalculateView();

		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		void CalculateViewProjection();

		void OnUpdate(DeltaTime dt, glm::vec2 mousePos);

		glm::mat4 GetViewProjection() { return m_ViewProjectionMatrix; }

		glm::vec3 GetTranslation() { return m_Translation; }
		glm::vec3 GetRotation() { return m_Rotation; }
		glm::vec3 GetScale() { return { m_Size * m_AspectRatio, m_Size, 1.0f }; }

	private:
		friend class LanternLayer;
		glm::vec3 m_Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}