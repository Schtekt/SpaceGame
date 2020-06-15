  
workspace "SpaceGame"
configurations { "Debug", "Release" }
location "build"
    
project "SpaceGame"
kind "ConsoleApp"
language "C++"
targetdir "bin/%{cfg.buildcfg}"
files { "src/**.*" }
vpaths {
    ["headers/"] = { "**.h", "**.hpp" },
    ["sources/"] = {"**.c", "**.cpp"}
}
filter "configurations:*"
defines { "SFML_STATIC" }
includedirs { "dependencies/include"}
libdirs { "dependencies/lib" }
links
{
    "opengl32",
    "freetype",
    "winmm",
    "gdi32",
    "flac",
    "vorbisenc",
    "vorbisfile",
    "vorbis",
    "ogg",
    "ws2_32"
}

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"
links
{	
    "sfml-graphics-s-d",
    "sfml-window-s-d",
    "sfml-system-s-d",
    "sfml-audio-s-d",
    "sfml-network-s-d"
}

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"
links
{	
    "sfml-graphics-s",
    "sfml-window-s",
    "sfml-system-s",
    "sfml-audio-s",
    "sfml-network-s"
}