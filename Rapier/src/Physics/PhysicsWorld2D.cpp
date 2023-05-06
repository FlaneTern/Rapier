#include "ipch.h"

#include "Time/DeltaTime.h"
#include "Physics/PhysicsWorld2D.h"


namespace Rapier 
{
	PhysicsWorld2D::PhysicsWorld2D()
	{
	}

	PhysicsWorld2D::PhysicsWorld2D(glm::vec2 gravity)
		: m_Gravity(gravity)
	{
	}

	void PhysicsWorld2D::OnUpdate(DeltaTime dt) 
	{
		for (auto& rigidBody : m_RigidBodies) 
		{
			rigidBody->OnUpdate(dt, m_Gravity);
		}

		BroadPhase();
		NarrowPhase();

		
	}

	Ref<RigidBody2D> PhysicsWorld2D::CreateRigidBody(RigidBody2DData data, RigidBody2DProperties props) 
	{
		m_RigidBodies.push_back(std::make_shared<RigidBody2D>(data, props));
		return m_RigidBodies.back();
	}


	// TODO
	static bool SATCollide(Ref<RigidBody2D> rigidBody1, Ref<RigidBody2D> rigidBody2) 
	{ 
		return false; 
	}

	static bool AABBCollide(Ref<RigidBody2D> rigidBody1, Ref<RigidBody2D> rigidBody2) 
	{
		glm::mat2x2 rb1Rotation = {
			{  glm::cos(glm::radians(rigidBody1->m_Rotation)), glm::sin(glm::radians(rigidBody1->m_Rotation))},
			{ -glm::sin(glm::radians(rigidBody1->m_Rotation)), glm::cos(glm::radians(rigidBody1->m_Rotation))}
		};

		glm::mat2x2 rb2Rotation = {
			{  glm::cos(glm::radians(rigidBody2->m_Rotation)), glm::sin(glm::radians(rigidBody2->m_Rotation))},
			{ -glm::sin(glm::radians(rigidBody2->m_Rotation)), glm::cos(glm::radians(rigidBody2->m_Rotation))}
		};

		glm::vec2 rb1Vertices[4] = {
			rigidBody1->m_Position + glm::vec2{ -rigidBody1->m_HalfScale.x, -rigidBody1->m_HalfScale.y } * rb1Rotation,
			rigidBody1->m_Position + glm::vec2{  rigidBody1->m_HalfScale.x, -rigidBody1->m_HalfScale.y } * rb1Rotation,
			rigidBody1->m_Position + glm::vec2{  rigidBody1->m_HalfScale.x,  rigidBody1->m_HalfScale.y } * rb1Rotation,
			rigidBody1->m_Position + glm::vec2{ -rigidBody1->m_HalfScale.x,  rigidBody1->m_HalfScale.y } * rb1Rotation
		};

		glm::vec2 rb2Vertices[4] = {
			rigidBody2->m_Position + glm::vec2{ -rigidBody2->m_HalfScale.x, -rigidBody2->m_HalfScale.y } * rb2Rotation,
			rigidBody2->m_Position + glm::vec2{  rigidBody2->m_HalfScale.x, -rigidBody2->m_HalfScale.y } * rb2Rotation,
			rigidBody2->m_Position + glm::vec2{  rigidBody2->m_HalfScale.x,  rigidBody2->m_HalfScale.y } * rb2Rotation,
			rigidBody2->m_Position + glm::vec2{ -rigidBody2->m_HalfScale.x,  rigidBody2->m_HalfScale.y } * rb2Rotation
		};

		float rb1XMin = rb1Vertices[0].x;
		float rb1XMax = rb1Vertices[0].x;
		float rb1YMin = rb1Vertices[0].y;
		float rb1YMax = rb1Vertices[0].y;

		float rb2XMin = rb2Vertices[0].x;
		float rb2XMax = rb2Vertices[0].x;
		float rb2YMin = rb2Vertices[0].y;
		float rb2YMax = rb2Vertices[0].y;

		for (size_t i = 1; i < 4; i++) 
		{
			rb1XMin	= std::min(rb1XMin, rb1Vertices[i].x);
			rb1XMax	= std::max(rb1XMax, rb1Vertices[i].x);
			rb1YMin	= std::min(rb1YMin, rb1Vertices[i].y);
			rb1YMax	= std::max(rb1YMax, rb1Vertices[i].y);

			rb2XMin = std::min(rb2XMin, rb2Vertices[i].x);
			rb2XMax = std::max(rb2XMax, rb2Vertices[i].x);
			rb2YMin = std::min(rb2YMin, rb2Vertices[i].y);
			rb2YMax = std::max(rb2YMax, rb2Vertices[i].y);
		}

		return (rb1XMax >= rb2XMin && rb2XMax >= rb1XMin)
			&& (rb1YMax >= rb2YMin && rb2YMax >= rb1YMin);
	}

	void PhysicsWorld2D::BroadPhase() 
	{
		for(size_t i = 0; i < m_RigidBodies.size() - 1; i++)
		{
			for (size_t j = i + 1; j < m_RigidBodies.size(); j++) 
			{
				if (AABBCollide(m_RigidBodies[i], m_RigidBodies[j]))
					m_BroadPhaseResult.push_back({ m_RigidBodies[i], m_RigidBodies[j] });
			}
		}

	}

	void PhysicsWorld2D::NarrowPhase() 
	{
		if (!m_BroadPhaseResult.empty())
			RAPIER_CORE_INFO("COLLISION DETECTED!!");

		m_BroadPhaseResult.clear();
	}

	void PhysicsWorld2D::ResolveCollision(Ref<RigidBody2D> rigidBody1, Ref<RigidBody2D> rigidBody2) 
	{


		// what am i supposed to do here

	}
}