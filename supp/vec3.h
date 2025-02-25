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

/**
 *  @brief Returns a new instance of `vec_3` by given x, y, z.
 */
t_vec3 vec3_new(float x, float y, float z);

/**
 *  @brief Printout the given instance of `vec_3`.
 */
void vec3_print(t_vec3 *vec);

/**
 * @brief Adds two `vec_3` and stores the result in the first vector.
 * 
 * @param vec1 A pointer to `t_vec3` which will be updated.
 * @param vec2 A pointer to `t_vec3` whose values will be added to `vec_1`.
 * 
 * @return A pointer to the modified `vec1`.
 * 
 * @note It's a in-place addition, so `vec1` is modified.
 */
t_vec3 *vec3_self_add(t_vec3 *vec1, t_vec3 *vec2);
t_vec3 vec3_minus(t_vec3 vec);

/**
 * @brief Multiply the given `vec_3` with given scalar in-place.
 * 
 * @param vec A pointer to `t_vec3` which will be updated.
 * @param scalar The scalar to multiply.
 * 
 * @return A pointer to the modified `vec`.
 * 
 * @note It's a in-place multiplication, so `vec` is modified.
 */
t_vec3 *vec3_self_mul(t_vec3 *vec, float scalar);

/**
 * @brief Divide the given `vec_3` with given scalar in-place.
 * 
 * @param vec A pointer to `t_vec3` which will be updated.
 * @param scalar The scalar to divide.
 * 
 * @return A pointer to the modified `vec`.
 * 
 * @note It's an in-place division, so `vec` is modified.
 */
t_vec3 *vec3_self_div(t_vec3 *vec, float scalar);

float vec3_length_squared(t_vec3 *vec);
float vec3_length(t_vec3 *vec);

t_vec3 vec3_add_vec(t_vec3 *vec, t_vec3 other);
t_vec3 vec3_sub_vec(t_vec3 vec, t_vec3 other);
t_vec3 vec3_mul_vec(t_vec3 vec, t_vec3 other);
t_vec3 vec3_div_vec(t_vec3 vec, t_vec3 other);

t_vec3 vec3_cross(t_vec3 vec, t_vec3 other);
float vec3_dot(t_vec3 vec, t_vec3 other);
t_vec3 vec3_unit(t_vec3 vec);

#endif
