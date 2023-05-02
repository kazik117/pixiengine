project(glad VERSION 3.4.0 LANGUAGES C)

add_library(${PROJECT_NAME} STATIC "")
target_sources(${PROJECT_NAME}
    PUBLIC
        "include/glad/glad.h"
    PRIVATE
        "src/glad.c"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
