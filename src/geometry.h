#ifndef PIKUMA3D_GEOMETRY_H
#define PIKUMA3D_GEOMETRY_H

#include "vector.h"

typedef struct Triangle {
    int a, b, c;
} Triangle;

const Vector3 cube_vertices[8] = {
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
};

#endif//PIKUMA3D_GEOMETRY_H
