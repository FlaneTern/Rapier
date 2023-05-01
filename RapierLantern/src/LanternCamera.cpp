#include "ipch.h"

#include "LanternCamera.h"

namespace Rapier {

	LanternCamera::LanternCamera() {
		CalculateViewProjection();
	}

	void LanternCamera::CalculateViewProjection() {

		CalculateView();
		CalculateProjection();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	bool LanternCamera::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		if (e.GetYOffset() < 0)
			m_Size *= 1.1f;
		else
			m_Size *= 0.9f;

		CalculateViewProjection();
		return false;
	}


	void LanternCamera::OnUpdate(DeltaTime dt, glm::vec2 mousePos) {
		static glm::vec2 initialMousePos;
		static bool dragStarted = false;

		if (!dragStarted) {
			if (Input::IsMouseButtonPressed(RapierKey_MouseRight)) {
				dragStarted = true;
				initialMousePos = mousePos;
			}
		}
		else {
			if (Input::IsMouseButtonPressed(RapierKey_MouseRight)) {
				glm::vec2 delta = (mousePos - initialMousePos);
				m_Translation -= glm::vec3{ delta, 0.0f };
			}
			else {
				dragStarted = false;
			}
		}


		static float translationSpeed = 0.5f;
		static float rotationSpeed = 180.0f;

		if (Input::IsKeyPressed(RapierKey_W)) m_Translation.y += translationSpeed * m_Size * dt;
		if (Input::IsKeyPressed(RapierKey_S)) m_Translation.y -= translationSpeed * m_Size * dt;
		if (Input::IsKeyPressed(RapierKey_D)) m_Translation.x += translationSpeed * m_Size * dt;
		if (Input::IsKeyPressed(RapierKey_A)) m_Translation.x -= translationSpeed * m_Size * dt;

		if (Input::IsKeyPressed(RapierKey_LeftBracket))  m_Rotation.z += rotationSpeed * dt;
		if (Input::IsKeyPressed(RapierKey_RightBracket)) m_Rotation.z -= rotationSpeed * dt;

		if (Input::IsKeyPressed(RapierKey_Equal)) m_Size = std::max(m_Size - m_Size * 1.50f * dt, 0.0f);
		if (Input::IsKeyPressed(RapierKey_Minus)) m_Size = m_Size + m_Size * 1.50f * dt;

		CalculateViewProjection();
	}


	void LanternCamera::CalculateView() {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), { 1, 0 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), { 0, 1 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), { 0, 0 ,1 });

		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Translation) * rotation);
	}
}