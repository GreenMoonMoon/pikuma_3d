#ifndef PIKUMA3D_GEOMETRY_H
#define PIKUMA3D_GEOMETRY_H

#include "vector.h"

typedef struct Triangle {
    int a, b, c;
} Triangle;

#define CUBE_VERTEX_COUNT 8
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
#define CUBE_TRIANGLE_COUNT 12
const Triangle cube_triangles[CUBE_TRIANGLE_COUNT] = {
    {0, 1, 2}, {2, 3, 0},
    {1, 5, 6}, {6, 2, 1},
    {4, 5, 7}, {7, 6, 5},
    {0, 4, 7}, {7, 3, 0},
    {3, 2, 6}, {6, 7, 3},
    {4, 5, 1}, {1, 0, 4}
 };

#endif//PIKUMA3D_GEOMETRY_H
