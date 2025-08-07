#ifndef PIKUMA3D_GEOMETRY_H
#define PIKUMA3D_GEOMETRY_H

#include "vector.h"
#include "stdint.h"

typedef uint32_t Color;

typedef struct Vertex {
    Vec3 position;
    Color color;
} Vertex;

typedef struct Triangle {
    union {
        struct { int a, b, c; };
        int raw[3];
    };
} Triangle;

typedef struct Transform {
    Vec3 position;
    Vec3 size;
    Vec3 rotation;
} Transform;

// Uses stb_ds dynamic arrays, which hold length and capacity information.
typedef struct Mesh {
    Vertex *vertices_list;
    Triangle *triangles_list;

    Transform transform;
} Mesh;

void free_mesh(Mesh mesh);

Mesh generate_cube_mesh(void);

Mesh load_obj(const char *filename);

#endif//PIKUMA3D_GEOMETRY_H
