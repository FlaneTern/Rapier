#include "ipch.h"
#include "Time/Timer.h"
#include "PerformanceStats.h"

namespace Rapier 
{

	Timer::Timer(const std::string& name)
		: m_Name(name)
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer() 
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		float duration = std::chrono::duration_cast<std::chrono::duration<float>>(endTime - m_StartTime).count() * 1000;

		PerformanceStats::AddFunctionTime({ m_Name, duration });
	}
}