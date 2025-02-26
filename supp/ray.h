#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct s_ray
{
    t_point3 *origin;
    t_vec3 *direction;
} t_ray;

/**
 * @brief construct a ray on heap.
 */
s_ray *ray_new(t_point3 *origin, t_vec3 *direction)
{
    s_ray *ray = (s_ray *)malloc(sizeof(s_ray));
    if (!ray)
        return NULL;
    ray->origin = origin;
    ray->direction = direction;
    return ray;
}

/**
 * @brief free the ray.
 */
void ray_free(s_ray **ray)
{
    if (ray && *ray)
    {
        free(*ray);
        *ray = NULL;
    }
}

/**
 * @brief get the point on the ray at distance t.
 *
 * @param ray the ray.
 * @param t the distance.
 * @return the point.
 */
t_point3 ray_at(s_ray *ray, double t)
{
    t_point3 result = vec3_new(ray->origin->x + t * ray->direction->x,
                               ray->origin->y + t * ray->direction->y,
                               ray->origin->z + t * ray->direction->z);
    return result;
}

#endif