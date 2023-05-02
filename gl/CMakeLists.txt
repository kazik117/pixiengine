project(opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME}
    PRIVATE
        "src/main.cxx"
)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw)
