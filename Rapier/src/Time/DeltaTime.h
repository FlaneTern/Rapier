#pragma once
#include <chrono>

namespace Rapier
{

	class RAPIER_API DeltaTime 
	{
	public:
		DeltaTime(std::chrono::high_resolution_clock::time_point prevTime);

		inline float GetSeconds() const { return dt; }
		inline float GetMilliSeconds() const { return dt * 1000.0f; }

		operator float() const { return dt; }
	private:
		float dt = 0;
	};

}