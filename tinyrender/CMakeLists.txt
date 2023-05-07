project(tiny-render LANGUAGES C)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME}
    PRIVATE
        "src/tiny_render.c"
        "src/line.h"
        "src/line.c"
        "src/utils.h"
)
target_link_libraries(${PROJECT_NAME} PRIVATE sr)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_executable(${PROJECT_NAME}-bench "")
    target_sources(${PROJECT_NAME}-bench
        PRIVATE
            "src/benchmark.c"
            "src/line.h"
            "src/line.c"
            "src/utils.h"
    )
    target_link_libraries(${PROJECT_NAME}-bench PRIVATE sr)
    target_compile_options(${PROJECT_NAME}-bench PRIVATE -pg)
    target_link_options(${PROJECT_NAME}-bench PRIVATE -pg)
endif()