#ifndef PIKUMA3D_GEOMETRY_H
#define PIKUMA3D_GEOMETRY_H

#include "vector.h"

typedef struct Triangle {
    int a, b, c;
} Triangle;

// Uses stb_ds dynamic arrays, which hold length and capacity information.
typedef struct Mesh {
    Vector3 *vertices_list;
    Triangle *triangles_list;
    int triangle_count;
} Mesh;

void free_mesh(Mesh mesh);

Mesh generate_cube_mesh(void);

#endif//PIKUMA3D_GEOMETRY_H
