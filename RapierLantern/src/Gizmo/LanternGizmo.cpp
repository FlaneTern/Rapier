#include "Rapier.h"
#include "LanternCamera.h"
#include "LanternGizmo.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"


namespace Rapier {

	///////////////////////////////////////////////////////////////////////////////////////////////
	// TODO: Disable depth test on gizmo instead of using z coords ? //////////////////////////////
	// TODO: Fix scale = 0                                           //////////////////////////////
	// TODO: Implement 3D Gizmo...                                   //////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	static constexpr float widthScale = 0.05f;
	static constexpr float heightScale = 0.2f;
	static constexpr float edgeScale = 0.2f;

	std::vector<Entity> LanternGizmo::s_GizmoEntities;

	bool LanternGizmo::s_HoveredX = false;
	bool LanternGizmo::s_HoveredY = false;

	GizmoState LanternGizmo::s_GizmoState = GizmoState::Translation;

	LanternCamera LanternGizmo::s_Camera;


	static glm::vec2 l_InitialMousePos;

	static bool l_DragStartedX = false;
	static bool l_DragStartedY = false;

	static float l_GizmoScaleX;
	static float l_GizmoScaleY;


	void LanternGizmo::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() != RapierKey_LeftCtrl)
			return;

		switch (s_GizmoState)
		{
		case GizmoState::Translation:
		{
			s_GizmoState = GizmoState::Rotation;
			break;
		}
		case GizmoState::Rotation:
		{
			s_GizmoState = GizmoState::Scale;
			break;
		}
		case GizmoState::Scale:
		{
			s_GizmoState = GizmoState::Translation;
			break;
		}
		}
	}

	void LanternGizmo::OnUpdate(DeltaTime dt, LanternCamera camera, glm::vec2 mousePos, int entityId) {
		TIME_FUNCTION_INTERNAL(LanternGizmo::OnUpdate);

		static glm::vec2 initialMousePos;
		
		s_Camera = camera;

		if (entityId == -2)
			s_HoveredX = true;
		else
			s_HoveredX = false;

		if (entityId == -3)
			s_HoveredY = true;
		else
			s_HoveredY = false;

		if (entityId == -4)
		{
			s_HoveredX = true;
			s_HoveredY = true;
		}

		if (Input::IsMouseButtonPressed(RapierKey_MouseLeft))
		{
			if (!l_DragStartedX && !l_DragStartedY)
			{
				if (s_HoveredX)
					l_DragStartedX = true;
				if (s_HoveredY)
					l_DragStartedY = true;

			}
			else
			{
				
				switch (s_GizmoState)
				{
				case GizmoState::Translation:
				{
					glm::vec2 delta = (mousePos - initialMousePos);
					for (auto& entity : s_GizmoEntities)
					{
						auto& transformComponent = entity.GetComponent<TransformComponent>();

						float zRotation = s_Camera.GetRotation().z;
							
						glm::mat2x2 rotation =
						{
							{ glm::cos(glm::radians((zRotation))),  glm::sin(glm::radians((zRotation))) },
							{-glm::sin(glm::radians((zRotation))),  glm::cos(glm::radians((zRotation))) },
						};
							
						if (l_DragStartedX)
						{
							glm::vec2 vx = rotation * glm::vec2{ 1.0f, 0.0f };
							glm::vec2 tx = glm::dot(delta, vx) * vx;
							transformComponent.Translation += glm::vec3{ tx, 0.0f };
						}

						if (l_DragStartedY)
						{
							glm::vec2 vy = rotation * glm::vec2{ 0.0f, 1.0f };
							glm::vec2 ty = glm::dot(delta, vy) * vy;
							transformComponent.Translation += glm::vec3{ ty, 0.0f };
						}

					}

					break;
				}
				case GizmoState::Rotation:
				{
					auto& transform = s_GizmoEntities[0].GetComponent<TransformComponent>();
					glm::vec2 relativeInitialMousePos = glm::normalize(initialMousePos - glm::vec2{ transform.Translation.x, transform.Translation.y });
					glm::vec2 relativeCurrentMousePos = glm::normalize(mousePos - glm::vec2{ transform.Translation.x, transform.Translation.y });
					float angle = glm::degrees(glm::orientedAngle(relativeInitialMousePos, relativeCurrentMousePos));

					for (auto& entity : s_GizmoEntities)
					{
						auto& transformComponent = entity.GetComponent<TransformComponent>();
						transformComponent.Rotation.z += angle;
					}

					break;
				}
				case GizmoState::Scale:
				{
					auto& transform = s_GizmoEntities[0].GetComponent<TransformComponent>();;

					float newGizmoScaleX = l_GizmoScaleX * (mousePos.x - transform.Translation.x) / (initialMousePos.x - transform.Translation.x);
					float newGizmoScaleY = l_GizmoScaleY * (mousePos.y - transform.Translation.y) / (initialMousePos.y - transform.Translation.y);

					for (auto& entity : s_GizmoEntities)
					{
						auto& entityTransform = entity.GetComponent<TransformComponent>();

						if (l_DragStartedX)
						{
							entityTransform.Scale.x /= l_GizmoScaleX;
							entityTransform.Scale.x *= newGizmoScaleX;
						}

						if (l_DragStartedY)
						{
							entityTransform.Scale.y /= l_GizmoScaleY;
							entityTransform.Scale.y *= newGizmoScaleY;
						}
					}

					if (l_DragStartedX && (mousePos.x - transform.Translation.x) != 0.0f)
						l_GizmoScaleX = newGizmoScaleX;
					if (l_DragStartedY && (mousePos.y - transform.Translation.y) != 0.0f)
						l_GizmoScaleY = newGizmoScaleY;

				}
				}

			}
			initialMousePos = mousePos;
		}
		else
		{
			l_DragStartedX = false;
			l_DragStartedY = false;
			l_GizmoScaleX = 1.0f;
			l_GizmoScaleY = 1.0f;
		}


	}

	GizmoRenderDataTranslation LanternGizmo::GetRenderDataTranslation() {
		TIME_FUNCTION_INTERNAL(LanternGizmo::GetRenderDataTranslation);



		GizmoRenderDataTranslation data;

		auto& transform = s_GizmoEntities[0].GetComponent<TransformComponent>();
		glm::vec3 translation = transform.Translation;
		glm::vec3 rotation = s_Camera.GetRotation();

		float height = s_Camera.GetSize() * heightScale;
		glm::vec3 scaleXQuad = { height, height * widthScale,    1.0f };
		glm::vec3 scaleYQuad = { height * widthScale,    height, 1.0f };
		glm::vec3 ScaleEdgeQuad = { height * edgeScale, height * edgeScale, 1.0f };

		glm::mat4 rotationMat =
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0 ,1 });


		translation.z += 2.0f;

		data.TransformMidCircle =
			glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		translation.z -= 1.0f;


		data.TransformXCircleEdge =
			glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { height * (1.0f - widthScale * 0.5f), 0.0f, 0.0f })
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		data.TransformXQuad =
			glm::translate(glm::mat4(1.0f), translation + glm::vec3{ height * (0.5f * 1.0f - widthScale * 0.5f) , 0.0f, 0.0f })
			* glm::translate(glm::mat4(1.0f), { -height * 0.5f * (1.0f - widthScale), 0.0f, 0.0f })
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { height * 0.5f * (1.0f - widthScale), 0.0f, 0.0f })
			* glm::scale(glm::mat4(1.0f), scaleXQuad);


		data.TransformYCircleEdge =
			glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { 0.0f, height * (1.0f - widthScale * 0.5f), 0.0f })
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		data.TransformYQuad =
			glm::translate(glm::mat4(1.0f), translation + glm::vec3{ 0.0f, height * (0.5f * 1.0f - widthScale * 0.5f), 0.0f })
			* glm::translate(glm::mat4(1.0f), { 0.0f, -height * 0.5f * (1.0f - widthScale), 0.0f })
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { 0.0f,  height * 0.5f * (1.0f - widthScale), 0.0f })
			* glm::scale(glm::mat4(1.0f), scaleYQuad);
		

		if ((s_HoveredX && !l_DragStartedX && !l_DragStartedY) || l_DragStartedX)
			data.ColorX = { 1.0f, 0.0f, 0.0f, 1.0f };

		if ((s_HoveredY && !l_DragStartedX && !l_DragStartedY) || l_DragStartedY)
			data.ColorY = { 1.0f, 0.0f, 0.0f, 1.0f };

		if ((s_HoveredX && s_HoveredY && !l_DragStartedX && !l_DragStartedY) || (l_DragStartedX && l_DragStartedY))
			data.ColorMidCircle = { 1.0f, 0.0f, 0.0f, 1.0f };
		
		return data;

	}

	GizmoRenderDataRotation LanternGizmo::GetRenderDataRotation() {
		TIME_FUNCTION_INTERNAL(LanternGizmo::GetRenderDataRotation);

		GizmoRenderDataRotation data;

		auto& transform = s_GizmoEntities[0].GetComponent<TransformComponent>();

		float height = s_Camera.GetSize() * heightScale;

		data.Transform =  glm::translate(glm::mat4(1.0f), transform.Translation)
						* glm::scale(glm::mat4(1.0f), { height, height, 1.0f });

		data.Transform[3][2] += 1.0f;

		if (s_HoveredX)
			data.Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		return data;
	}

	GizmoRenderDataScale LanternGizmo::GetRenderDataScale() {
		TIME_FUNCTION_INTERNAL(LanternGizmo::GetRenderDataScale);

		GizmoRenderDataScale data;

		auto& transform = s_GizmoEntities[0].GetComponent<TransformComponent>();
		glm::vec3 translation = transform.Translation;
		glm::vec3 rotation = transform.Rotation;

		float height = s_Camera.GetSize() * heightScale;
		glm::vec3 scaleXQuad = { height * l_GizmoScaleX, height * widthScale,    1.0f };
		glm::vec3 scaleYQuad = { height * widthScale,    height * l_GizmoScaleY, 1.0f };
		glm::vec3 ScaleEdgeQuad = { height * edgeScale, height * edgeScale, 1.0f };

		glm::mat4 rotationMat = 
			  glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1 ,0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0 ,1 });


		translation.z += 2.0f;

		data.TransformMidQuad = 
			glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		translation.z -= 1.0f;


		data.TransformXQuadEdge = 
			  glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { height * (l_GizmoScaleX - widthScale * 0.5f), 0.0f, 0.0f })
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		data.TransformXQuad = 
			  glm::translate(glm::mat4(1.0f), translation + glm::vec3{ height * (0.5f * l_GizmoScaleX - widthScale * 0.5f) , 0.0f, 0.0f})
			* glm::translate(glm::mat4(1.0f), { -height * 0.5f * (l_GizmoScaleX - widthScale), 0.0f, 0.0f })
			* rotationMat
			* glm::translate(glm::mat4(1.0f), {  height * 0.5f * (l_GizmoScaleX - widthScale), 0.0f, 0.0f })
			* glm::scale(glm::mat4(1.0f), scaleXQuad);


		data.TransformYQuadEdge = 
			  glm::translate(glm::mat4(1.0f), translation)
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { 0.0f, height * (l_GizmoScaleY - widthScale * 0.5f), 0.0f })
			* glm::scale(glm::mat4(1.0f), ScaleEdgeQuad);

		data.TransformYQuad = 
			  glm::translate(glm::mat4(1.0f), translation + glm::vec3{ 0.0f, height * (0.5f * l_GizmoScaleY - widthScale * 0.5f), 0.0f })
			* glm::translate(glm::mat4(1.0f), { 0.0f, -height * 0.5f * (l_GizmoScaleY - widthScale), 0.0f })
			* rotationMat
			* glm::translate(glm::mat4(1.0f), { 0.0f,  height * 0.5f * (l_GizmoScaleY - widthScale), 0.0f })
			* glm::scale(glm::mat4(1.0f), scaleYQuad);




		if ((s_HoveredX && !l_DragStartedX && !l_DragStartedY) || l_DragStartedX)
			data.ColorX = { 1.0f, 0.0f, 0.0f, 1.0f };

		if ((s_HoveredY && !l_DragStartedX && !l_DragStartedY) || l_DragStartedY)
			data.ColorY = { 1.0f, 0.0f, 0.0f, 1.0f };

		if ((s_HoveredX && s_HoveredY && !l_DragStartedX && !l_DragStartedY) || (l_DragStartedX && l_DragStartedY))
			data.ColorMidQuad = { 1.0f, 0.0f, 0.0f, 1.0f };

		return data;
	}


	void LanternGizmo::CreateGizmo(Entity& entity) {
		s_GizmoEntities.push_back(entity);
	}

	void LanternGizmo::ClearGizmo() {
		s_GizmoEntities.clear();
	}
}