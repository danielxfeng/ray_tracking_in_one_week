#include "proj.h"
#include "vec3.h"
#include <math.h>

t_vec3 vec3_new(float x, float y, float z)
{
    t_vec3 vec = {x, y, z};
    return vec;
}

void vec3_print(t_vec3 *vec)
{
    printf("x: %f, y: %f, z: %f\n", vec->x, vec->y, vec->z);
}

t_vec3 *vec3_self_add(t_vec3 *vec1, t_vec3 *vec2)
{
    vec1->x = vec1->x + vec2->x;
    vec1->y = vec1->y + vec2->y;
    vec1->z = vec1->z + vec2->z;
    return (vec1);
}

t_vec3 *vec3_self_sub(t_vec3 *vec1, t_vec3 *vec2)
{
    vec1->x = vec1->x - vec2->x;
    vec1->y = vec1->y - vec2->y;
    vec1->z = vec1->z - vec2->z;
    return (vec1);
}

t_vec3 *vec3_self_mul(t_vec3 *vec, float scalar)
{
    vec->x = vec->x * scalar;
    vec->y = vec->y * scalar;
    vec->z = vec->z * scalar;
    return (vec);
}

t_vec3 *vec3_self_div(t_vec3 *vec, float scalar)
{
    vec->x = vec->x / scalar;
    vec->y = vec->y / scalar;
    vec->z = vec->z / scalar;
    return (vec);
}

t_vec3 vec3_flip_minus(t_vec3 *vec)
{
    return vec3_new(-vec->x, -vec->y, -vec->z);
}

float vec3_length_squared(t_vec3 *vec)
{
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

float vec3_length(t_vec3 *vec)
{
    return sqrt(vec3_length_squared(vec));
}

t_vec3 vec3_add_vecs(t_vec3 *vec1, t_vec3 *vec2)
{
    return vec3_new(vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z);
}

t_vec3 vec3_sub_vecs(t_vec3 *vec1, t_vec3 *vec2)
{
    return vec3_new(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
}

t_vec3 vec3_mul_vecs(t_vec3 *vec1, t_vec3 *vec2)
{
    return vec3_new(vec1->x * vec2->x, vec1->y * vec2->y, vec1->z * vec2->z);
}

t_vec3 vec3_mul_vec(t_vec3 *vec, float scalar)
{
    return vec3_new(vec->x * scalar, vec->y * scalar, vec->z * scalar);
}

t_vec3 vec3_div_vec(t_vec3 *vec, float scalar)
{
    return vec3_new(vec->x / scalar, vec->y / scalar, vec->z / scalar);
}

float vec3_dot(t_vec3 *vec1, t_vec3 *vec2)
{
    return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}

t_vec3 vec3_cross(t_vec3 *vec1, t_vec3 *vec2)
{
    return vec3_new(vec1->y * vec2->z - vec1->z * vec2->y,
                    vec1->z * vec2->x - vec1->x * vec2->z,
                    vec1->x * vec2->y - vec1->y * vec2->x);
}

t_vec3 vec3_unit(t_vec3 *vec)
{
    float len = vec3_length(vec);
    assert(len != 0);
    return vec3_div_vec(vec, len);
}

t_vec3 vec3_random()
{
    return vec3_new(RANDOM_FLOAT, RANDOM_FLOAT, RANDOM_FLOAT);
}

t_vec3 vec3_random_range(float min, float max)
{
    return vec3_new(RANDOM_FLOAT_RANGE(min, max), RANDOM_FLOAT_RANGE(min, max), RANDOM_FLOAT_RANGE(min, max));
}

t_vec3 vec3_random_unit_vector()
{
    while (1)
    {
        t_vec3 vec = vec3_random_range(-1, 1);
        float len_sq = vec3_length_squared(&vec);
        if (len_sq > 1e-12 && len_sq <= 1)
            return vec3_div_vec(&vec, sqrt(len_sq));
    }
}

t_vec3 vec3_random_on_hemisphere (t_vec3 *normal)
{
    t_vec3 random = vec3_random_unit_vector();
    if (vec3_dot(&random, normal) > 0)
        return random;
    return vec3_flip_minus(&random);
}

bool vec3_near_zero(t_vec3 *vec)
{
    const float s = 1e-8;
    return fabsf(vec->x) < s && fabsf(vec->y) < s && fabsf(vec->z) < s;
}

t_vec3 vec3_reflect(t_vec3 *v, t_vec3 *n)
{
    t_vec3 vec = vec3_mul_vec(n, 2 * vec3_dot(v, n));
    return vec3_sub_vecs(v, &vec);
}

t_vec3 vec3_refract(t_vec3 *uv, t_vec3 *n, float etai_over_etat)
{
    t_vec3 fliped_uv = vec3_flip_minus(uv);
    float cos_theta = fminf(vec3_dot(&fliped_uv, n), 1.0);
    t_vec3 temp1 = vec3_mul_vec(n, cos_theta);
    t_vec3 temp2 = vec3_add_vecs(uv, &temp1);
    t_vec3 r_out_perp = vec3_mul_vec(&temp2, etai_over_etat);
    t_vec3 r_out_parallel = vec3_mul_vec(n, -sqrtf(fabsf((float)1.0 - vec3_length_squared(&r_out_perp))));
    return vec3_add_vecs(&r_out_perp, &r_out_parallel);
}
