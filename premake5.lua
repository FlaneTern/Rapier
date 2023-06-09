workspace "Rapier"
	architecture "x64"
	startproject "RapierLantern"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Rapier/vendor/GLFW/include"
IncludeDir["Glad"] = "Rapier/vendor/Glad/include"
IncludeDir["ImGui"] = "Rapier/vendor/ImGui"
IncludeDir["glm"] = "Rapier/vendor/glm"
IncludeDir["stb"] = "Rapier/vendor/stb"
IncludeDir["entt"] = "Rapier/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Rapier/vendor/yaml-cpp/include"

include "Rapier/vendor/GLFW"
include "Rapier/vendor/Glad"
include "Rapier/vendor/ImGui"
include "Rapier/vendor/yaml-cpp"

project "Rapier"
	location "Rapier"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")

	pchheader "ipch.h"
	pchsource "Rapier/src/ipch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/RapierEntryPoint.h",
		"%{prj.name}/Rapier.h",
		"%{prj.name}/res/**",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	links{
		"Glad",
		"GLFW",
		"ImGui",
		"opengl32.lib",
		"yaml-cpp"
	}

	postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/RapierLantern")
        }


	systemversion "latest"
	defines{
		"RAPIER_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

	filter "configurations:Debug"
		defines "RAPIER_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "RAPIER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RAPIER_DIST"
		runtime "Release"
		optimize "on"

	

project "Forehead"
	location "Forehead"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/res/**",
	}

	includedirs{
		"%{prj.name}/src",
		"Rapier/vendor/spdlog/include",
		"Rapier",
		"Rapier/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	links{
		"Rapier",
		"RapierLantern"
	}

	defines "RAPIER_BUILD_SCRIPT"

	systemversion "latest"

	postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/RapierLantern")
        }

	filter "configurations:Debug"
		defines "RAPIER_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "RAPIER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RAPIER_DIST"
		runtime "Release"
		optimize "on"




project "RapierLantern"
	location "RapierLantern"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/res/**",
	}

	includedirs{
		"%{prj.name}/src",
		"Rapier/vendor/spdlog/include",
		"Rapier",
		"Rapier/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}
	 
	links{
		"Rapier",
		"ImGui"
	}


	systemversion "latest"

	filter "configurations:Debug"
		defines "RAPIER_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "RAPIER_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RAPIER_DIST"
		runtime "Release"
		optimize "on"