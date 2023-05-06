#include "ipch.h"

#ifdef RAPIER_DEBUG

#include "Renderer/DebugRenderer.h"
#include "Scene/Scene.h"

namespace Rapier 
{
	void DebugRenderer::DrawLine(Scene* scene, const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color) 
	{
		auto renderer = scene->GetDebugRenderer();
		renderer->DrawLine(p0, p1, color);
	}

	void DebugRenderer::DrawBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color)
	{
		auto renderer = scene->GetDebugRenderer();
		renderer->DrawTexture(glm::translate(glm::mat4(1.0f), center), nullptr, color);
	}

	void DebugRenderer::DrawWireBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color) 
	{
		auto renderer = scene->GetDebugRenderer();

		glm::vec3 p0 = { center.x - halfSize.x, center.y - halfSize.y, 0.0f };
		glm::vec3 p1 = { center.x + halfSize.x, center.y - halfSize.y, 0.0f };
		glm::vec3 p2 = { center.x + halfSize.x, center.y + halfSize.y, 0.0f };
		glm::vec3 p3 = { center.x - halfSize.x, center.y + halfSize.y, 0.0f };

		renderer->DrawLine(p0, p1, color);
		renderer->DrawLine(p1, p2, color);
		renderer->DrawLine(p2, p3, color);
		renderer->DrawLine(p3, p0, color);
	}

	void DebugRenderer::DrawCircle(Scene* scene, const glm::vec3& center, float radius, const glm::vec4& color) 
	{
		auto renderer = scene->GetDebugRenderer();
		renderer->DrawCircle(center, glm::vec2{ radius, radius }, nullptr, color);
	}

	void DebugRenderer::DrawWireCircle(Scene* scene, const glm::vec3& center, float innerRadius, float outerRadius, const glm::vec4& color) 
	{
		RAPIER_CORE_ASSERT(innerRadius <= outerRadius, "Inner radius is greater than outer radius !");
		auto renderer = scene->GetDebugRenderer();

		renderer->DrawCircle(center, glm::vec2{ outerRadius, outerRadius }, nullptr, color, -1,
			innerRadius / outerRadius);
	}


	// Gizmos

	void DebugRenderer::GizmoDrawBox(Scene* scene, const glm::mat4& transform, const glm::vec4& color, int entityId)
	{
		auto renderer = scene->GetDebugRenderer();
		renderer->DrawTexture(transform, nullptr, color, entityId);
	}

	void DebugRenderer::GizmoDrawCircle(Scene* scene, const glm::mat4& transform, const glm::vec4& color, int entityId, float innerRadiusScale) 
	{
		auto renderer = scene->GetDebugRenderer();
		renderer->DrawCircle(transform, nullptr, color, entityId, innerRadiusScale);
	}

}

#endif