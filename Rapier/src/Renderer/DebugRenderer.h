#pragma once

#include "glm/glm.hpp"

namespace Rapier 
{
	class Scene;
	class LanternLayer;

	class RAPIER_API DebugRenderer 
	{

#ifdef RAPIER_DEBUG
	public:
		static void DrawLine(Scene* scene, const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color);
		static void DrawBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color);
		static void DrawWireBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color);
		static void DrawCircle(Scene* scene, const glm::vec3& center, float radius, const glm::vec4& color);
		static void DrawWireCircle(Scene* scene, const glm::vec3& center, float innerRadius, float outerRadius , const glm::vec4& color);

	private:
		friend class LanternLayer;
		static void GizmoDrawBox(Scene* scene, const glm::mat4& transform, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1);
		static void GizmoDrawCircle(Scene* scene, const glm::mat4& transform, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, int entityId = -1, float innerRadiusScale = 0.0f);

#else
		inline static void DrawLine(Scene* scene, const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color) {}
		inline static void DrawBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color) {}
		inline static void DrawWireBox(Scene* scene, const glm::vec3& center, const glm::vec3& halfSize, const glm::vec4& color) {}
		inline static void DrawCircle(Scene* scene, const glm::vec3& center, float radius, const glm::vec4& color) {}
		inline static void DrawWireCircle(Scene* scene, const glm::vec3& center, float innerRadius, float outerRadius, const glm::vec4& color) {}
#endif

	};

}