project(example LANGUAGES C)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME}
    PRIVATE
        "src/main.c"
)
target_link_libraries(${PROJECT_NAME} sr)
