#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace IRENE {

	class IRENE_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

#define IRENE_CORE_TRACE(...) ::IRENE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IRENE_CORE_INFO(...)  ::IRENE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IRENE_CORE_WARN(...)  ::IRENE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IRENE_CORE_ERROR(...) ::IRENE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IRENE_CORE_FATAL(...) ::IRENE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define IRENE_TRACE(...) ::IRENE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define IRENE_INFO(...)  ::IRENE::Log::GetClientLogger()->info(__VA_ARGS__)
#define IRENE_WARN(...)  ::IRENE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IRENE_ERROR(...) ::IRENE::Log::GetClientLogger()->error(__VA_ARGS__)
#define IRENE_FATAL(...) ::IRENE::Log::GetClientLogger()->fatal(__VA_ARGS__)
