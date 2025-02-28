#include "hittable.h"

bool hit(t_sphere *sphere, t_ray *r, float t_min, float t_max, t_hit_record *rec);

t_sphere sphere_new(t_point3 center, float radius)
{
    t_sphere sphere;

    sphere.sphere_center = center;
    if (radius < 0)
        radius = 0;
    sphere.sphere_radius = radius;
    sphere.hit = hit;
    return sphere;
}

bool hit(t_sphere *sphere, t_ray *ray, float t_min, float t_max, t_hit_record *rec)
{
    t_vec3 oc = vec3_sub_vecs(&sphere->center, ray->origin);
    float a = vec3_length_squared(ray->direction);
    float h = vec3_dot(ray->direction, &oc);
    float c = vec3_length_squared(&oc) - sphere->radius * sphere->radius;
    float discriminant = h * h - a * c;

    if (discriminant < 0)
        return false;

    float sqrtd = sqrt(discriminant);

    float root = (h - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (h + sqrtd) / a;
        if (root <= t_min || t_max <= root)
            return false;
    }

    rec->t = root;
    rec->p = ray_at(ray, root);
    t_vec3 temp = vec3_sub_vecs(&sphere->p, &sphere->center);
    t_vec3 outward_normal = vec3_div_vec(&temp, sphere->radius);
    set_face_normal(ray, &outward_normal, rec);

    return true;
}