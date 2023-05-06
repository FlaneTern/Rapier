#include "ipch.h"



#include "Physics/RigidBody2D.h"

namespace Rapier 
{

	RigidBody2D::RigidBody2D(RigidBody2DData data)
		: m_Position(data.Position), m_Rotation(data.Rotation), m_Velocity(data.Velocity),
		  m_Acceleration(data.Acceleration), m_HalfScale(data.HalfScale) {}

	RigidBody2D::RigidBody2D(RigidBody2DProperties props)
		: m_Properties(props) {}

	RigidBody2D::RigidBody2D(RigidBody2DData data, RigidBody2DProperties props)
		: m_Position(data.Position), m_Rotation(data.Rotation), m_Velocity(data.Velocity),
		m_Acceleration(data.Acceleration), m_HalfScale(data.HalfScale), m_Properties(props) {}

	void RigidBody2D::OnUpdate(DeltaTime dt, const glm::vec2& gravity) 
	{
		if (m_Properties.Type == RigidBodyType::Static)
			return;

		m_Acceleration += gravity / m_Properties.Mass;
		m_Velocity += (float)dt * m_Acceleration;
		m_Position += (float)dt * m_Velocity;

		m_Acceleration = { 0.0f, 0.0f };
	}

	void RigidBody2D::ApplyForce(const glm::vec2& force) 
	{
		if (m_Properties.Type == RigidBodyType::Static) 
		{
			RAPIER_CORE_ASSERT(false, "Rigid Body is static !");
			return;
		}

		m_Acceleration += force / m_Properties.Mass;
	}
}