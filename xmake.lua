set_project("RubicCubeSimulator")

add_rules("mode.debug", "mode.release")

add_requires("glfw")

set_languages("c++17")

if is_plat("macosx") then 
    set_defaultarchs("arm64")
else 
    set_defaultarchs("x64")
end

target("RubicCubeSimulator")
    add_packages("glfw")
    set_kind("binary")
    add_files("*/*.cpp", "main.cpp")
    set_targetdir("./build")