#include "hittable.h"

bool hit(t_sphere *sphere, t_ray *r, float t_min, float t_max);

t_sphere sphere_new(t_point3 center, float radius)
{
    t_hit_record sphere;

    sphere.sphere_center = center;
    if (radius < 0)
        radius = 0;
    sphere.sphere_radius = radius;
    sphere.hit = hit;
    sphere.set_face_normal = set_face_normal;
    return sphere;
}

bool hit(t_sphere *sphere, t_ray *ray, float t_min, float t_max)
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

    sphere->t = root;
    sphere->p = ray_at(ray, root);
    t_vec3 temp = vec3_sub_vecs(&sphere->p, &sphere->center);
    sphere->normal = vec3_div_vec(&temp, sphere->radius);

    return true;
}