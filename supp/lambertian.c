#include "lambertian.h"

bool lambertian_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);

t_material *lambertian_new(t_color albedo)
{
    t_lambertian *lambertian = malloc(sizeof(t_lambertian));
    if (!lambertian)
    {
        perror("malloc");
        exit(1);
    }
    lambertian->albedo = albedo;
    lambertian->scatter = lambertian_scatter;
    return lambertian;
}

bool lambertian_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    t_vec3 rand = vec3_random_unit_vector();
    t_vec3 scatter_direction = vec3_add_vecs(&rec->normal, &rand);
    if (vec3_near_zero(&scatter_direction))
        scatter_direction = rec->normal;
    *scattered = ray_new(&rec->p, &scatter_direction);
    *attenuation = mat->albedo;
    return true;
}
