#include "ray.h"
#include <stdlib.h>

/**
 * @brief construct a ray on heap.
 */
t_ray *ray_new(t_point3 *origin, t_vec3 *direction)
{
    t_ray *ray = (t_ray *)malloc(sizeof(t_ray));
    if (!ray)
        return NULL;
    t_point3 *origin_copy = (t_point3 *)malloc(sizeof(t_point3));
    if (!origin_copy)
    {
        free(ray);
        return NULL;
    }
    t_vec3 *direction_copy = (t_vec3 *)malloc(sizeof(t_vec3));
    if (!direction_copy)
    {
        free(origin_copy);
        free(ray);
        return NULL;
    }
    *origin_copy = vec3_new(origin->x, origin->y, origin->z);
    *direction_copy = vec3_new(direction->x, direction->y, direction->z);
    ray->origin = origin_copy;
    ray->direction = direction_copy;
    return ray;
}

/**
 * @brief free the ray.
 */
void ray_free(t_ray **ray)
{
    if (ray && *ray)
    {
        free((*ray)->origin);
        free((*ray)->direction);
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
t_point3 ray_at(t_ray *ray, double t)
{
    t_point3 result = vec3_new(ray->origin->x + t * ray->direction->x,
                               ray->origin->y + t * ray->direction->y,
                               ray->origin->z + t * ray->direction->z);
    return result;
}