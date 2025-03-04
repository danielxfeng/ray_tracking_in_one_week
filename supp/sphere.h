#ifndef SPHERE_H
#define SPHERE_H

# include "hittable.h"

typedef t_hittable t_sphere;

t_sphere *sphere_new(t_point3 center, float radius, t_material *material);

#endif