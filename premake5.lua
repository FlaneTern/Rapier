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

include "Irene/vendor/GLFW"
include "Irene/vendor/Glad"
include "Irene/vendor/ImGui"

project "Irene"
	location "Irene"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ipch.h"
	pchsource "Irene/src/ipch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/EntryPoint.h",
		"%{prj.name}/Irene.h"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links{
		"Glad",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}

	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"
	defines{
		"IRENE_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Forehead")
	}

	filter "configurations:Debug"
		defines{
			"IRENE_DEBUG",
			"IRENE_ENABLE_ASSERTS"
		}
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "IRENE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "IRENE_DIST"
		buildoptions "/MD"
		optimize "On"

	

project "Forehead"
	location "Forehead"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"Irene/vendor/spdlog/include",
		"Irene"
	}
	 
	links{
		"Irene"
	}

	cppdialect "C++20"
	staticruntime "On"
	systemversion "latest"

	filter "configurations:Debug"
		defines "IRENE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "IRENE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "IRENE_DIST"
		buildoptions "/MD"
		optimize "On"