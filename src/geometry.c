//
// Created by josue on 2025-08-04.
//
#include "geometry.h"
#define STB_DS_IMPLEMENTATION
#include "external/stb_ds.h"

#define CUBE_VERTEX_COUNT 8
#define CUBE_TRIANGLE_COUNT 12
const Vector3 cube_vertices[CUBE_VERTEX_COUNT] = {
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
};
const Triangle cube_triangles[CUBE_TRIANGLE_COUNT] = {
    {0, 1, 2}, {2, 3, 0},
    {1, 5, 6}, {6, 2, 1},
    {4, 5, 7}, {7, 6, 5},
    {0, 4, 7}, {7, 3, 0},
    {3, 2, 6}, {6, 7, 3},
    {4, 5, 1}, {1, 0, 4}
};

void free_mesh(Mesh m) {
   if (m.vertices_list) { arrfree(m.vertices_list); }
   if (m.triangles_list) { arrfree(m.triangles_list); }
}

Mesh generate_cube_mesh(void) {
    Mesh cube = {0};
    arrsetlen(cube.vertices_list, CUBE_VERTEX_COUNT);
    memcpy(cube.vertices_list, cube_vertices, sizeof cube_vertices);
    arrsetlen(cube.triangles_list, CUBE_TRIANGLE_COUNT);
    memcpy(cube.triangles_list, cube_triangles, sizeof cube_triangles);

    cube.triangle_count = CUBE_TRIANGLE_COUNT;

    cube.transform = (Transform){ {0}, {1.0f}, {0}};

    return cube;
}
