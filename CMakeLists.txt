cmake_minimum_required(VERSION 3.26)
project(opengl-native)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(gl)
add_subdirectory(framework)
add_subdirectory(example)
add_subdirectory(tinyrender)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
