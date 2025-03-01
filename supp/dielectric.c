#include "proj.h"
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

static float reflectance(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1 - r0) * powf((1 - cosine), 5);
}

bool dielectric_scatter(t_material *mat, t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray **scattered)
{
    *attenuation = vec3_new(1, 1, 1);
    float r1 = rec->front_face ? (1.0 / mat->ref_idx) : mat->ref_idx;

    t_vec3 unit_direction = vec3_unit(r_in->direction);
    t_vec3 neg_unit_direction = vec3_flip_minus(&unit_direction);

    float cos_theta = fminf(vec3_dot(&neg_unit_direction, &rec->normal), 1.0);
    float sin_theta = sqrtf(1.0 - cos_theta * cos_theta);

    bool cannot_refract = r1 * sin_theta > 1.0;
    t_vec3 direction;

    if (cannot_refract || reflectance(cos_theta, r1) > RANDOM_FLOAT)
        direction = vec3_reflect(&unit_direction, &rec->normal);
    else
        direction = vec3_refract(&unit_direction, &rec->normal, r1);

    *scattered = ray_new(&rec->p, &direction);
    return true;
}
