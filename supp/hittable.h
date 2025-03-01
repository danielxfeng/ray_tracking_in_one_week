#ifndef HITTABLE_H
#define HITTABLE_H

# include "vec3.h"
# include "ray.h"
# include "interval.h"
# include "material.h"

typedef struct s_material t_material;

typedef struct s_hit_record
{
    t_point3 p;
    t_vec3 normal;
    t_material *material;
    float t;
    bool front_face;
} t_hit_record;

typedef struct s_hittable t_hittable;

typedef struct s_hittable
{
    t_point3 sphere_center;
    float sphere_radius;
    t_material *material;

    bool (*hit)(t_hittable *hittable, t_ray *r, t_interval *interval, t_hit_record *rec);
} t_hittable;

void set_face_normal(t_ray *r, t_vec3 *outward_normal, t_hit_record *rec);

#endif