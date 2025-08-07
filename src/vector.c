#include <math.h>
#include "vector.h"

Vec2 vec2_add(const Vec2 a, const Vec2 b) {
    return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 vec2_subtract(const Vec2 a, const Vec2 b) {
    return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 vec2_multiply(const Vec2 a, const Vec2 b) {
    return (Vec2){a.x * b.x, a.y * b.y};
}

Vec2 vec2_scale(const Vec2 vec, const float scalar) {
    return (Vec2){vec.x * scalar, vec.y * scalar};
}

Vec2 vec2_divide(const Vec2 a, const Vec2 b) {
    return (Vec2){a.x / b.x, a.y / b.y};
}

Vec2 vec2_divide_scalar(const Vec2 vec, const float scalar) {
    return (Vec2){vec.x / scalar, vec.y / scalar};
}

float vec2_length_squared(const Vec2 vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

float vec2_length(const Vec2 vec) {
    return sqrtf(vec2_length_squared(vec));
}

Vec3 vec3_rotate_x(const Vec3 vec, const float angle) {
    return (Vec3){
        vec.x,
        vec.y * cosf(angle) - vec.z * sinf(angle),
        vec.z * cosf(angle) + vec.y * sinf(angle)
    };
}

Vec3 vec3_rotate_y(const Vec3 vec, const float angle) {
    return (Vec3){
        vec.x * cosf(angle) - vec.z * sinf(angle),
        vec.y,
        vec.z * cosf(angle) + vec.x * sinf(angle)
    };
}
Vec3 vec3_rotate_z(const Vec3 vec, const float angle) {
    return (Vec3){
        vec.x * cosf(angle) - vec.y * sinf(angle),
        vec.y * cosf(angle) + vec.x * sinf(angle),
        vec.z
    };
}

Vec3 vec3_add(const Vec3 a, const Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3_subtract(const Vec3 a, const Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 vec3_multiply(const Vec3 a, const Vec3 b) {
    return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

Vec3 vec3_scale(const Vec3 vec, const float scalar) {
    return (Vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

Vec3 vec3_divide(const Vec3 a, const Vec3 b) {
    return (Vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

Vec3 vec3_divide_scalar(const Vec3 vec, const float scalar) {
    return (Vec3){vec.x / scalar, vec.y / scalar, vec.z / scalar};
}

float vec3_length_squared(const Vec3 vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

float vec3_length(const Vec3 vec) {
    return sqrtf(vec3_length_squared(vec));
}

Vec3 vec3_cross(const Vec3 a, const Vec3 b) {
    return (Vec3){
        .x = a.y * b.z - b.y * a.y,
        .y = a.z * b.x - b.z * a.x,
        .z = a.x * b.y - b.x * a.y
    };
}

float vec3_dot(const Vec3 a, const Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
