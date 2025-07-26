#ifndef PIKUMA3D_VECTOR_H
#define PIKUMA3D_VECTOR_H

typedef struct Vector2 {
    float x, y;
} Vector2;

typedef struct Vector3 {
    float x, y, z;
} Vector3;

typedef struct IVector2 {
    int x, y;
} IVector2;

Vector3 rotate_x(Vector3 vector, float angle);

Vector3 rotate_y(Vector3 vector, float angle);

Vector3 rotate_z(Vector3 vector, float angle);

#endif//PIKUMA3D_VECTOR_H
