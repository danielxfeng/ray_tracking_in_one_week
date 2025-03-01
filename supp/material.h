#ifndef MATERIAL_H
#define MATERIAL_H
#include "hittable.h"
#include "color.h"

typedef struct s_material t_material;
typedef struct s_hit_record t_hit_record;

typedef struct s_material
{
    t_color albedo;
    float fuzz;
    float ref_idx;

    bool (*scatter)(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);
} t_material;

void material_free(t_material **material);

#endif