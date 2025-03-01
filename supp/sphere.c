#include "sphere.h"

bool hit(t_sphere *sphere, t_ray *r, t_interval *interval, t_hit_record *rec);

t_sphere *sphere_new(t_point3 center, float radius, t_material *material)
{
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
    {
        perror("malloc");
        exit(1);
    }
    sphere->sphere_center = center;
    if (radius < 0)
        radius = 0;
    sphere->sphere_radius = radius;
    sphere->hit = hit;
    sphere->material = material;
    return sphere;
}

bool hit(t_sphere *sphere, t_ray *ray, t_interval *interval, t_hit_record *rec)
{
    t_vec3 oc = vec3_sub_vecs(&sphere->sphere_center, ray->origin);
    float a = vec3_length_squared(ray->direction);
    float h = vec3_dot(ray->direction, &oc);
    float c = vec3_length_squared(&oc) - sphere->sphere_radius * sphere->sphere_radius;
    float discriminant = h * h - a * c;

    if (discriminant < 0)
        return false;

    float sqrtd = sqrt(discriminant);

    float root = (h - sqrtd) / a;
    if (!interval_surrounds(interval, root))
    {
        root = (h + sqrtd) / a;
        if (!interval_surrounds(interval, root))
            return false;
    }

    rec->t = root;
    rec->p = ray_at(ray, root);
    t_vec3 temp = vec3_sub_vecs(&rec->p, &sphere->sphere_center);
    t_vec3 outward_normal = vec3_div_vec(&temp, sphere->sphere_radius);
    rec->material = sphere->material;
    set_face_normal(ray, &outward_normal, rec);

    return true;
}