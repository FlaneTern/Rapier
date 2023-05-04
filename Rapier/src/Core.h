#pragma once

#include <memory>
#include <vector>

#pragma warning(disable : 4251)


#ifdef RAPIER_BUILD_DLL
	#define RAPIER_API __declspec(dllexport)
#else
	#define RAPIER_API __declspec(dllimport)
#endif

#ifdef RAPIER_BUILD_SCRIPT
#define RAPIER_SCRIPT_API __declspec(dllexport)
#else
#define RAPIER_SCRIPT_API __declspec(dllimport)
#endif


#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1) 

#ifdef RAPIER_DEBUG
#define RAPIER_ENABLE_ASSERTS
#endif

#ifdef RAPIER_ENABLE_ASSERTS
#define RAPIER_ASSERT(x, ...) { if(!(x)) {RAPIER_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); }}
#define RAPIER_CORE_ASSERT(x, ...) { if(!(x)) {RAPIER_CORE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define RAPIER_ASSERT(x, ...)
#define RAPIER_CORE_ASSERT(x, ...)
#endif

namespace Rapier {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	using RapierData = std::vector<std::byte>;

	typedef uint32_t RendererId;
}

