#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

//
// A lightweight 3D vector library
// can be further optimized by using SIMD instructions.
//

typedef struct s_vec3
{
    float x;
    float y;
    float z;
} t_vec3;

typedef t_vec3 t_point3;

t_vec3 *vec3_new(float x, float y, float z);
void vec3_free(t_vec3 *vec);
void vec3_print(t_vec3 *vec);

t_vec3 *vec3_add(t_vec3 *vec, t_vec3 *other);
t_vec3 *vec3_minus(t_vec3 *vec);
t_vec3 *vec3_mul(t_vec3 *vec, float scalar);
t_vec3 *vec3_div(t_vec3 *vec, float scalar);

float vec3_length_squared(t_vec3 *vec);
float vec3_length(t_vec3 *vec);

t_vec3 *vec3_add_vec(t_vec3 *vec, t_vec3 *other);
t_vec3 *vec3_sub_vec(t_vec3 *vec, t_vec3 *other);
t_vec3 *vec3_mul_vec(t_vec3 *vec, t_vec3 *other);
t_vec3 *vec3_div_vec(t_vec3 *vec, t_vec3 *other);

t_vec3 *vec3_cross(t_vec3 *vec, t_vec3 *other);
float vec3_dot(t_vec3 *vec, t_vec3 *other);
t_vec3 *vec3_unit(t_vec3 *vec);

#endif
