#include "dielectric.h"

bool dielectric_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered);

t_material *dielectric_new(float ref_idx)
{
    t_material *dielectric = malloc(sizeof(t_dielectric));
    if (!dielectric)
    {
        perror("malloc");
        exit(1);
    }
    dielectric->ref_idx = ref_idx;
    dielectric->scatter = dielectric_scatter;
    return dielectric;
}

bool dielectric_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    *attenuation = vec3_new(1, 1, 1);
    float r1 = rec->front_face ? (1.0 / mat->ref_idx) : mat->ref_idx;

    t_vec3 unit_direction = vec3_unit(r_in->direction);
    t_vec3 refraction_direction = vec3_refract(&unit_direction, &rec->normal, r1);

    *scattered = ray_new(&rec->p, &refraction_direction);
    return true;
}
