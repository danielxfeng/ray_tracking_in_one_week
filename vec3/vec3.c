#include "vec3.h"

t_vec3 vec3_new(float x, float y, float z)
{
    t_vec3 vec = {x, y, z};
    return vec;
}

void vec3_print(t_vec3 vec)
{
    printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

t_vec3 vec3_add(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

t_vec3 vec3_minus(t_vec3 vec)
{
    return vec3_new(-vec.x, -vec.y, -vec.z);
}

t_vec3 vec3_mul(t_vec3 vec, float scalar)
{
    return vec3_new(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

t_vec3 vec3_div(t_vec3 vec, float scalar)
{
    assert(scalar != 0);
    return vec3_new(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

float vec3_length_squared(t_vec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

float vec3_length(t_vec3 vec)
{
    return sqrt(vec3_length_squared(vec));
}

t_vec3 vec3_add_vec(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

t_vec3 vec3_sub_vec(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

t_vec3 vec3_mul_vec(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

t_vec3 vec3_div_vec(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

float vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

t_vec3 vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
    return vec3_new(vec1.y * vec2.z - vec1.z * vec2.y,
                    vec1.z * vec2.x - vec1.x * vec2.z,
                    vec1.x * vec2.y - vec1.y * vec2.x);
}

t_vec3 vec3_unit(t_vec3 vec)
{
    float len = vec3_length(vec);
    assert(len != 0);
    return vec3_div(vec, len);
}
