#pragma once
#include "Time/DeltaTime.h"
#include "glm/glm.hpp"

namespace Rapier {
	enum class RigidBodyType {
		Static,
		Dynamic
	};
	

	struct RigidBody2DData {
		glm::vec2 Position = { 0.0f, 0.0f };
		float Rotation = 0.0f;
		glm::vec2 Velocity = { 0.0f, 0.0f };
		glm::vec2 Acceleration = { 0.0f, 0.0f };
		glm::vec2 HalfScale = { 0.5f, 0.5 };
	};

	struct RigidBody2DProperties {
		RigidBodyType Type = RigidBodyType::Dynamic;
		bool FixedRotation = false;
		float Mass = 1.0f;
		float FrictionCoefficient = 0.2f;
		float Restitution = 0.3f;
	};

	class RAPIER_API RigidBody2D {
	public:
		RigidBody2D() = default;
		RigidBody2D(RigidBody2DData data);
		RigidBody2D(RigidBody2DProperties props);
		RigidBody2D(RigidBody2DData data, RigidBody2DProperties props);


		void OnUpdate(DeltaTime dt, const glm::vec2& gravity);

		void ApplyForce(const glm::vec2& force);


		// Fields supposed to be private ?
		// Remove getter and setter ?
		void SetPosition(const glm::vec2& position) { m_Position = position; }
		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		void SetAcceleration(const glm::vec2& acceleration) { m_Acceleration = acceleration; }

		glm::vec2 GetPosition() const { return m_Position; }
		glm::vec2 GetVelocity() const { return m_Velocity; }
		glm::vec2 GetAcceleration() const { return m_Acceleration; }

		RigidBody2DData GetData() const { return { m_Position, m_Rotation, m_Velocity, m_Acceleration, m_HalfScale }; }
		RigidBody2DProperties GetProperties() const { return m_Properties; }

		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		glm::vec2 m_Velocity = { 0.0f, 0.0f };
		glm::vec2 m_Acceleration = { 0.0f, 0.0f };
		
		glm::vec2 m_HalfScale = { 0.5f, 0.5 };

		RigidBody2DProperties m_Properties;

	private:


	};

}