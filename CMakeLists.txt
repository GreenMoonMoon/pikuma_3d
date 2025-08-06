cmake_minimum_required(VERSION 3.18)
project(pikuma3d)
set(CMAKE_C_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.18
)
FetchContent_MakeAvailable(SDL)

add_executable(pikuma3d)
target_sources(pikuma3d PRIVATE
        src/main.c
        src/draw.c
        src/vector.c
        src/geometry.c
        src/obj_parser.c
)
target_link_libraries(pikuma3d PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(
            TARGET pikuma3d POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:pikuma3d>
            VERBATIM
    )
endif()

add_subdirectory(test)