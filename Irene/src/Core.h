#pragma once

#ifdef IRENE_BUILD_DLL
#define IRENE_API __declspec(dllexport)
#else
#define IRENE_API __declspec(dllimport)
#endif