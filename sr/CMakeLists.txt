project(sr VERSION 0.0.1 LANGUAGES C)

add_library(${PROJECT_NAME} STATIC "")
target_sources(${PROJECT_NAME}
    PUBLIC
        "include/sr/app.h"
        "include/sr/pixel.h"
        "include/sr/sprite.h"
        "include/sr/error.h"
    PRIVATE
        "src/app_private.h"
        "src/app.c"
        "src/pixel.c"
        "src/platform_private.h"
        "src/platform.c"
        "src/sprite_private.h"
        "src/sprite.c"
)
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw)

if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()
