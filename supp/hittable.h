#ifndef HITTABLE_H
#define HITTABLE_H

# include "ray.h"
# include <stdbool.h>
# include <math.h>

typedef t_hit_record t_sphere;

typedef struct s_hit_record
{
    t_point3 p;
    t_vec3 normal;
    float t;
    bool front_face;

    void (*set_face_normal)(t_hit_record *rec, t_ray *r, t_vec3 *outward_normal);
    bool (*hit)(t_hit_record *rec, t_ray *r, float t_min, float t_max);

    t_point3 sphere_center;
    float sphere_radius;
} t_hit_record;

void set_face_normal(t_hit_record *rec, t_ray *r, t_vec3 *outward_normal);

#endif