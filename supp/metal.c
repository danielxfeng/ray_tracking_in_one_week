#include "metal.h"

bool metal_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);

t_material *metal_new(t_color albedo)
{
    t_metal *metal = malloc(sizeof(t_metal));
    if (!metal)
    {
        perror("malloc");
        exit(1);
    }
    metal->albedo = albedo;
    metal->scatter = metal_scatter;
    return metal;
}

bool metal_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    t_vec3 refected = vec3_reflect(r_in->direction, &rec->normal);
    *scattered = ray_new(&rec->p, &refected);
    *attenuation = mat->albedo;
    return true;
}