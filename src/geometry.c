//
// Created by josue on 2025-08-04.
//
#include "geometry.h"
#define STB_DS_IMPLEMENTATION
#include "external/stb_ds.h"
#define FAST_OBJ_IMPLEMENTATION
#include "external/fast_obj.h"

#define CUBE_VERTEX_COUNT 8
#define CUBE_TRIANGLE_COUNT 12
const Vertex cube_vertices[CUBE_VERTEX_COUNT] = {
    {{-0.5f, -0.5f, -0.5f}, 0xFF0FFFFF},
    {{0.5f, -0.5f, -0.5f}, 0xFFFFFFFF},
    {{0.5f, 0.5f, -0.5f}, 0xFFFFFFFF},
    {{-0.5f, 0.5f, -0.5f}, 0xFFFFFFFF},
    {{-0.5f, -0.5f, 0.5f}, 0xFFFFFFFF},
    {{0.5f, -0.5f, 0.5f}, 0xFFFFFFFF},
    {{0.5f, 0.5f, 0.5f}, 0xFFFFFFFF},
    {{-0.5f, 0.5f, 0.5f}, 0xFFFFFFFF},
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

    cube.transform = (Transform){ {0}, {1.0f}, {0}};

    return cube;
}

Mesh load_obj(const char* filename) {
    fastObjMesh *fmesh = fast_obj_read(filename);

    Mesh mesh = {0};

    arrsetlen(mesh.vertices_list, fmesh->position_count);
    for (int i = 0; i < fmesh->position_count; ++i) {
        mesh.vertices_list[i] = (Vertex){
            .position = (Vec3){
                .x = fmesh->positions[i * 3],
                .y = fmesh->positions[i * 3 + 1],
                .z = fmesh->positions[i * 3 + 2]
            },
            // .color = fmesh->colors[i]
        };
    }

    arrsetlen(mesh.triangles_list, fmesh->face_count);
    int index = 0;
    for (int i = 0; i < fmesh->face_count; ++i) {
        mesh.triangles_list[i].a = fmesh->indices[index].p;
        mesh.triangles_list[i].b = fmesh->indices[index + 1].p;
        mesh.triangles_list[i].c = fmesh->indices[index + 2].p;

        // assume all faces are triangles.
        // TODO: implement a triangulation algorithm for non-triangular faces
        index += fmesh->face_vertices[i];
    };

    // mesh.triangle_count = ;
    mesh.transform = (Transform){
        .position = (Vec3){0},
        .size = (Vec3){1.0f},
        .rotation = (Vec3){0}
    };

    return mesh;
}
