include_directories(${PROJECT_SOURCE_DIR})

set(test_SOURCE_FILES ../src/obj_parser.c ../src/geometry.c ../src/vector.c ../src/draw.c )
add_executable(test_obj_parser test_obj_parser.c ${test_SOURCE_FILES})

# Copy test files
add_custom_command(
        TARGET test_obj_parser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/test/test_cube.obj
        ${CMAKE_CURRENT_BINARY_DIR}/test_cube.obj
)