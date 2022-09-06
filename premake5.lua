workspace "Soli Game-Toolkit"
	architecture "x64"
	startproject "TestSpace"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}"

project "Soli-Rom Engine"
	location "Soli-Rom Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "precompiledheaders.h"
	pchsource "Soli-Rom Engine/src/precompiledheaders.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"Extra/SDL2-2.0.14/include",
		"Extra/SDL2-2.0.22/include",
		"Extra/SDL2_image-2.6.0/include",
		"%{prj.name}/src"
	}

	libdirs
	{
		--"Extra/SDL2-2.0.14/lib/x64/"
		"Extra/SDL2-2.0.22/lib/x64/",
		"Extra/SDL2_image-2.6.0/lib/x64/",

	}

	links
	{
		"SDL2",
		"SDL2main",
		"SDL2_image"
	}

	defines
	{
		"BUILD_DLL"
	}

	filter "configurations:Debug"
		defines "SOL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SOL_RELEASE"
		runtime "Release"
		optimize "on"


project "TestSpace"
	location "TestSpace"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
 
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		--"Extra/SDL2-2.0.14/include",
		"Extra/SDL2-2.0.22/include",
		"Extra/SDL2_image-2.6.0/include",
		"Soli-Rom Engine/src"
	}

	libdirs
	{
		--"Extra/SDL2-2.0.14/lib/x64/"
		"Extra/SDL2-2.0.22/lib/x64/",
		"Extra/SDL2_image-2.6.0/lib/x64/",
	}

	links
	{
		"SDL2",
		"SDL2main",
		"SDL2_image",
		"Soli-Rom Engine"
	}
	
	--postbuildcommands
	--{ -- relpath = relative path, copies EcoScape.dll to Sandbox
		--("{COPYFILE} %{SolutionDir}Extra/SDL2_image-2.6.0/lib/x64/SDL2_image.dll " .. outputdir.. "/Sandbox"),
		--("{COPYFILE} %{SolutionDir}Extra/SDL2-2.0.22/lib/x64/SDL2.dll " .. outputdir.. "/Sandbox")
	--}

	filter "configurations:Debug"
		defines "SOL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SOL_RELEASE"
		runtime "Release"
		optimize "on"