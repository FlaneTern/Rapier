#pragma once


namespace Rapier 
{

	class LanternCamera;
	class LanternLayer;

	enum class GizmoState
	{
		Translation,
		Rotation,
		Scale
	};


	struct GizmoRenderDataTranslation 
	{
		glm::mat4 TransformXQuad = glm::mat4(1.0f);
		glm::mat4 TransformYQuad = glm::mat4(1.0f);
		glm::mat4 TransformXCircleEdge = glm::mat4(1.0f);
		glm::mat4 TransformYCircleEdge = glm::mat4(1.0f);
		glm::mat4 TransformMidCircle = glm::mat4(1.0f);
		glm::vec4 ColorX = { 1.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 ColorY = { 1.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 ColorMidCircle = { 1.0f, 1.0f, 0.0f, 1.0f };
	};

	struct GizmoRenderDataRotation 
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		glm::vec4 Color = { 1.0f, 1.0f, 0.0f, 1.0f };
	};

	struct GizmoRenderDataScale 
	{
		glm::mat4 TransformXQuad = glm::mat4(1.0f);
		glm::mat4 TransformYQuad = glm::mat4(1.0f);
		glm::mat4 TransformXQuadEdge = glm::mat4(1.0f);
		glm::mat4 TransformYQuadEdge = glm::mat4(1.0f);
		glm::mat4 TransformMidQuad = glm::mat4(1.0f);
		glm::vec4 ColorX = { 1.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 ColorY = { 1.0f, 1.0f, 0.0f, 1.0f };
		glm::vec4 ColorMidQuad = { 1.0f, 1.0f, 0.0f, 1.0f };
	};

	class LanternGizmo
	{
	public:

		static void OnUpdate(DeltaTime dt, LanternCamera camera, glm::vec2 mousePos, int entityId);
		static void OnKeyReleasedEvent(KeyReleasedEvent& e);

		static GizmoRenderDataTranslation GetRenderDataTranslation();
		static GizmoRenderDataRotation GetRenderDataRotation();
		static GizmoRenderDataScale GetRenderDataScale();

		static void CreateGizmo(Entity& entity);
		static void ClearGizmo();

	private:
		LanternGizmo();
		friend class LanternLayer;

		static LanternCamera s_Camera;
		static bool s_HoveredX;
		static bool s_HoveredY;

		static GizmoState s_GizmoState;

		static std::vector<Entity> s_GizmoEntities;
	};
}