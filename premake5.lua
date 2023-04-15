workspace "Irene"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Irene/vendor/GLFW/include"
IncludeDir["Glad"] = "Irene/vendor/Glad/include"
IncludeDir["ImGui"] = "Irene/vendor/ImGui"
IncludeDir["glm"] = "Irene/vendor/glm"

include "Irene/vendor/GLFW"
include "Irene/vendor/Glad"
include "Irene/vendor/ImGui"

project "Irene"
	location "Irene"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")

	pchheader "ipch.h"
	pchsource "Irene/src/ipch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/EntryPoint.h",
		"%{prj.name}/Irene.h"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links{
		"Glad",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}


	systemversion "latest"
	defines{
		"IRENE_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Debug"
		defines "IRENE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "IRENE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IRENE_DIST"
		runtime "Release"
		optimize "on"

	

project "Forehead"
	location "Forehead"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"Irene/vendor/spdlog/include",
		"Irene",
		"%{IncludeDir.glm}"
	}
	 
	links{
		"Irene"
	}


	systemversion "latest"

	filter "configurations:Debug"
		defines "IRENE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "IRENE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IRENE_DIST"
		runtime "Release"
		optimize "on"