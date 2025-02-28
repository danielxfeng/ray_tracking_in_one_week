#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct s_ray
{
    t_point3 *origin;
    t_vec3 *direction;
} t_ray;

t_ray *ray_new(t_point3 *origin, t_vec3 *direction);
void ray_free(t_ray **ray);
t_point3 ray_at(t_ray *ray, double t);

#endif