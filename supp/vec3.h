#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

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

/**
 * @brief Substracts two `vec_3` and stores the result in the first vector.
 * 
 * @param vec1 A pointer to `t_vec3` which will be updated.
 * @param vec2 A pointer to `t_vec3` whose values will be substracted from `vec_1`.
 * 
 * @return A pointer to the modified `vec1`.
 * 
 * @note It's a in-place substraction, so `vec1` is modified.
 */
t_vec3 *vec3_self_sub(t_vec3 *vec1, t_vec3 *vec2);

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


/**
 * @brief Flip the given `vec_3` by apply `*-1` to each properties.
 * 
 * @param vec A pointer to `t_vec3` which will be updated.
 * 
 * @return An instance of flipped `vec_3`.
 */
t_vec3 vec3_flip_minus(t_vec3 *vec);

/**
 * @brief Returns the squared length of the given `vec_3`.
 * 
 * @param vec A pointer to `t_vec3`.
 * 
 * @return The squared length of the given `vec_3`.
 */
float vec3_length_squared(t_vec3 *vec);

/**
 * @brief Returns the length of the given `vec_3`.
 * 
 * @param vec A pointer to `t_vec3`.
 * 
 * @return The length of the given `vec_3`.
 */
float vec3_length(t_vec3 *vec);

/**
 * @brief Adds two `vec_3` and returns the result.
 * 
 * @param vec1 A pointer to `t_vec3`.
 * @param vec2 A pointer to `t_vec3`.
 * 
 * @return The result of the addition.
 */
t_vec3 vec3_add_vecs(t_vec3 *vec1, t_vec3 *vec2);

/**
 * @brief Subtracts two `vec_3` and returns the result.
 * 
 * @param vec1 A pointer to `t_vec3`.
 * @param vec2 A pointer to `t_vec3`.
 * 
 * @return The result of the subtraction.
 */
t_vec3 vec3_sub_vecs(t_vec3 *vec1, t_vec3 *vec2);

/**
 * @brief Multiplies two `vec_3` and returns the result.
 * 
 * @param vec1 A pointer to `t_vec3`.
 * @param vec2 A pointer to `t_vec3`.
 * 
 * @return The result of the multiplication.
 */
t_vec3 vec3_mul_vecs(t_vec3 *vec1, t_vec3 *vec2);

/**
 * @brief Multiplies the given `vec_3` with the given scalar and returns the result.
 * 
 * @param vec A pointer to `t_vec3`.
 * @param scalar The scalar to multiply.
 * 
 * @return The result of the multiplication.
 */
t_vec3 vec3_mul_vec(t_vec3 *vec, float scalar);

/**
 * @brief Divides the given `vec_3` with the given scalar and returns the result.
 * 
 * @param vec A pointer to `t_vec3`.
 * @param scalar The scalar to divide.
 * 
 * @return The result of the division.
 */
t_vec3 vec3_div_vec(t_vec3 *vec1, float scalar);

/**
 * @brief Returns the cross product of two `vec_3`.
 * 
 * @param vec1 A pointer to `t_vec3`.
 * @param vec2 A pointer to `t_vec3`.
 * 
 * @return The cross product of the two `vec_3`.
 */
t_vec3 vec3_cross(t_vec3 *vec1, t_vec3 *vec2);

/**
 * @brief Returns the dot product of two `vec_3`.
 * 
 * @param vec1 A pointer to `t_vec3`.
 * @param vec2 A pointer to `t_vec3`.
 * 
 * @return The dot product of the two `vec_3`.
 */
float vec3_dot(t_vec3 *vec1, t_vec3 *vec2);

/**
 * @brief Returns the unit vector of the given `vec_3`.
 * 
 * @param vec A pointer to `t_vec3`.
 * 
 * @return The unit vector of the given `vec_3`.
 */
t_vec3 vec3_unit(t_vec3 *vec);

/**
 * @brief Returns a random `vec_3` with each property in the range of [0, 1].
 * 
 * @return A random `vec_3`.
 */
t_vec3 vec3_random();

/**
 * @brief Returns a random `vec_3` with each property in the range of [min, max].
 * 
 * @param min The minimum value of each property.
 * @param max The maximum value of each property.
 * 
 * @return A random `vec_3`.
 */
t_vec3 vec3_random_range(float min, float max);

/**
 * @brief Returns a random unit vector.
 * 
 * @return A random unit vector.
 */
t_vec3 vec3_random_unit_vector();


/**
 * @brief Returns a random vector on the hemisphere.
 * 
 * @param normal A pointer to `t_vec3` which is the normal vector.
 * 
 * @return A random vector on the hemisphere.
 */
t_vec3 vec3_random_on_hemisphere (t_vec3 *normal);

/**
 * @brief Returns if the given `vec_3` is near zero.
 * 
 * @param vec A pointer to `t_vec3`.
 * 
 * @return `true` if the given `vec_3` is near zero, otherwise `false`.
 */
bool vec3_near_zero(t_vec3 *vec);

/**
 * @brief Returns the reflection of the given vector.
 * 
 * @param v A pointer to `t_vec3`.
 * @param n A pointer to `t_vec3`.
 * 
 * @return The reflection of the given vector.
 */
t_vec3 vec3_reflect(t_vec3 *v, t_vec3 *n);

/**
 * @brief Returns the refraction of the given vector.
 * 
 * @param uv A pointer to `t_vec3`.
 * @param n A pointer to `t_vec3`.
 * @param etai_over_etat The ratio of the refractive indices.
 * 
 * @return The refraction of the given vector.
 */
t_vec3 vec3_refract(t_vec3 *uv, t_vec3 *n, float etai_over_etat);

/**
 * @brief Returns a copy of the given `vec_3`.
 * 
 * @param vec A pointer to `t_vec3`.
 * 
 * @return A copy of the given `vec_3`.
 */
t_vec3 vec3_copy(t_vec3 *vec);

/**
 * @brief Returns a random vector in the unit disk.
 * 
 * @return A random vector in the unit disk.
 */
t_vec3 vec3_random_in_unit_disk();

#endif
