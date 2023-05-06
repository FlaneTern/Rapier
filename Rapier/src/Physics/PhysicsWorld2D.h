#pragma once

#include "Physics/RigidBody2D.h"

namespace Rapier 
{

	class RAPIER_API PhysicsWorld2D 
	{
	public:
		PhysicsWorld2D();
		PhysicsWorld2D(glm::vec2 gravity);

		void OnUpdate(DeltaTime dt);

		Ref<RigidBody2D> CreateRigidBody(RigidBody2DData data, RigidBody2DProperties props);

		

	private:
		glm::vec2 m_Gravity = glm::vec2{ 0.0f, -9.8f };
		std::vector<Ref<RigidBody2D>> m_RigidBodies;


	private:
		// Collision Detection
		void BroadPhase();
		void NarrowPhase();

		std::vector<std::pair<Ref<RigidBody2D>, Ref<RigidBody2D>>> m_BroadPhaseResult;



		
		// Collision Resolving
		void ResolveCollision(Ref<RigidBody2D> rigidBody1, Ref<RigidBody2D> rigidBody2);
	};

}