cmake_minimum_required(VERSION 3.18)
project(pikuma3d)
set(CMAKE_C_STANDARD 17)

add_executable(pikuma3d)
target_sources(pikuma3d PRIVATE
        src/main.c
        src/draw.c
        src/vector.c
)
target_link_libraries(pikuma3d PRIVATE SDL3)