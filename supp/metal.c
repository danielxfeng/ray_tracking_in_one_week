#include "metal.h"

bool metal_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);

t_material *metal_new(t_color albedo, float fuzz)
{
    t_metal *metal = malloc(sizeof(t_metal));
    if (!metal)
    {
        perror("malloc");
        exit(1);
    }
    metal->albedo = albedo;
    if (fuzz < 1)
        metal->fuzz = fuzz;
    else
        metal->fuzz = 1;
    metal->scatter = metal_scatter;
    return metal;
}

bool metal_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    t_vec3 refected = vec3_reflect(r_in->direction, &rec->normal);
    t_vec3 unit_vector = vec3_unit(&refected);
    t_vec3 rand = vec3_random_unit_vector();
    t_vec3 temp = vec3_mul_vec(&rand, mat->fuzz);
    refected = vec3_add_vecs(&refected, &temp);
    *scattered = ray_new(&rec->p, &refected);
    *attenuation = mat->albedo;
    return vec3_dot((*scattered)->direction, &rec->normal) > 0;
}