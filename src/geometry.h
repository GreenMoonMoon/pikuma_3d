#ifndef PIKUMA3D_GEOMETRY_H
#define PIKUMA3D_GEOMETRY_H

#include "vector.h"
#include "stdint.h"

typedef uint32_t Color;

typedef struct Vertex {
    Vector3 position;
    Color color;
} Vertex;

typedef struct Triangle {
    int a, b, c;
} Triangle;

typedef struct Transform {
    Vector3 position;
    Vector3 size;
    Vector3 rotation;
} Transform;

// Uses stb_ds dynamic arrays, which hold length and capacity information.
typedef struct Mesh {
    Vertex *vertices_list;
    Triangle *triangles_list;
    int triangle_count;

    Transform transform;
} Mesh;

void free_mesh(Mesh mesh);

Mesh generate_cube_mesh(void);

#endif//PIKUMA3D_GEOMETRY_H
