#ifndef PIKUMA3D_VECTOR_H
#define PIKUMA3D_VECTOR_H

typedef struct Vec2 {
    float x, y;
} Vec2;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct IVec2 {
    int x, y;
} IVec2;

Vec2 vec2_add(Vec2 a, Vec2 b);

Vec2 vec2_subtract(Vec2 a, Vec2 b);

Vec2 vec2_multiply(Vec2 a, Vec2 b);

Vec2 vec2_scale(Vec2 vec, float scalar);

Vec2 vec2_divide(Vec2 a, Vec2 b);

Vec2 vec2_divide_scalar(Vec2 vec, float scalar);

float vec2_length_squared(Vec2 vec);

float vec2_length(Vec2 vec);

Vec3 vec3_rotate_x(Vec3 vec, float angle);

Vec3 vec3_rotate_y(Vec3 vec, float angle);

Vec3 vec3_rotate_z(Vec3 vec, float angle);

Vec3 vec3_add(Vec3 a, Vec3 b);

Vec3 vec3_subtract(Vec3 a, Vec3 b);

Vec3 vec3_multiply(Vec3 a, Vec3 b);

Vec3 vec3_scale(Vec3 vec, float scalar);

Vec3 vec3_divide(Vec3 a, Vec3 b);

Vec3 vec3_divide_scalar(Vec3 vec, float scalar);

float vec3_length_squared(Vec3 vec);

float vec3_length(Vec3 vec);

Vec3 vec3_cross(Vec3 a, Vec3 b);

float vec3_dot(Vec3 a, Vec3 b);

#endif//PIKUMA3D_VECTOR_H
