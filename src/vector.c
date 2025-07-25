#include <math.h>
#include "vector.h"

Vector3 rotate_x(const Vector3 vector, const float angle) {
    return (Vector3){
        vector.x,
        vector.y * cosf(angle) - vector.z * sinf(angle),
        vector.z * cosf(angle) + vector.y * sinf(angle)
    };
}

Vector3 rotate_y(const Vector3 vector, const float angle) {
    return (Vector3){
        vector.x * cosf(angle) - vector.z * sinf(angle),
        vector.y,
        vector.z * cosf(angle) + vector.x * sinf(angle)
    };
}
Vector3 rotate_z(const Vector3 vector, const float angle) {
    return (Vector3){
        vector.x * cosf(angle) - vector.y * sinf(angle),
        vector.y * cosf(angle) + vector.x * sinf(angle),
        vector.z
    };
}
