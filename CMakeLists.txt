cmake_minimum_required(VERSION 3.15..3.26)
project(opengl-native)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(sr)
add_subdirectory(tinyrender)
add_subdirectory(example)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
