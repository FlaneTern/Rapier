#pragma once

namespace Rapier
{

	class RAPIER_API Timer 
	{
	public:
		Timer(const std::string& name = "Unknown Function Name");

		~Timer();
	private:
		std::string m_Name;
		std::chrono::high_resolution_clock::time_point m_StartTime;
	};

#define TIME_FUNCTION(x) { Timer timer(#x); x }
#define TIME_FUNCTION_INTERNAL(x) Timer timer(#x)
}