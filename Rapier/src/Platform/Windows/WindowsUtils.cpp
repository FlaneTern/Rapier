#include "ipch.h"
#include "FileSystem/FileSystem.h"
#include "Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <windows.h>
namespace Rapier {


	std::string FileSystem::OpenFileDialog(const std::string& filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter.c_str();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();

	}

	std::string FileSystem::SaveFileDialog(const std::string& filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetPlatformWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter.c_str();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter.c_str(), '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}


	void* FileSystem::LoadDLL(const std::string& filename) {
		if (s_ScriptHandle) {
			UnloadDLL(s_ScriptHandle);
			s_ScriptHandle = nullptr;
		}

		std::wstring wFilename = std::wstring(filename.begin(), filename.end());
		auto handle = LoadLibrary(wFilename.c_str());

		s_ScriptHandle = handle;

		return handle;
	}

	void* FileSystem::LoadDLLFunction(void* DLLHandle, const std::string& functionName) {

		void* func = (void*)GetProcAddress((HMODULE)DLLHandle, functionName.c_str());

		return func;
	}

	bool FileSystem::UnloadDLL(void* handle) {
		bool success = FreeLibrary((HMODULE)handle);
		if (success)
			s_ScriptHandle = nullptr;

		return success;
	}

}