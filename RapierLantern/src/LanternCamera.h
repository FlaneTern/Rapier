#pragma once

#include "Rapier.h"

#include "glm/glm.hpp"

namespace Rapier {
	class LanternLayer;

	class LanternCamera : public Camera {
	public:
		LanternCamera();

		void CalculateView();

		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		void SetViewportSize(uint32_t width, uint32_t height);
		void CalculateViewProjection();

		void OnUpdate(DeltaTime dt, glm::vec2 mousePos);

		glm::mat4 GetViewProjection() { return m_ViewProjectionMatrix; }

	private:
		friend class LanternLayer;
		glm::vec3 m_Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}