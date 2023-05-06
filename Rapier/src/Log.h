#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rapier 
{

	class RAPIER_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();

	};
}

#define RAPIER_CORE_TRACE(...) ::Rapier::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RAPIER_CORE_INFO(...)  ::Rapier::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RAPIER_CORE_WARN(...)  ::Rapier::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RAPIER_CORE_ERROR(...) ::Rapier::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RAPIER_CORE_FATAL(...) ::Rapier::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define RAPIER_TRACE(...) ::Rapier::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RAPIER_INFO(...)  ::Rapier::Log::GetClientLogger()->info(__VA_ARGS__)
#define RAPIER_WARN(...)  ::Rapier::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RAPIER_ERROR(...) ::Rapier::Log::GetClientLogger()->error(__VA_ARGS__)
#define RAPIER_FATAL(...) ::Rapier::Log::GetClientLogger()->fatal(__VA_ARGS__)
