#pragma once

#ifdef IRENE_BUILD_DLL
	#define IRENE_API __declspec(dllexport)
#else
	#define IRENE_API __declspec(dllimport)
#endif


#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1) 

#ifdef IRENE_ENABLE_ASSERTS
#define IRENE_ASSERT(x, ...) { if(!(x)) {IRENE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); }}
#define IRENE_CORE_ASSERT(x, ...) { if(!(x)) {IRENE_CORE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define IRENE_ASSERT(x, ...)
#define IRENE_CORE_ASSERT(x, ...)
#endif