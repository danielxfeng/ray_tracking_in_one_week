#include "../supp/proj.h"
#include "../supp/camera.h"
#include "../supp/sphere.h"
#include "../supp/material.h"
#include "../supp/lambertian.h"
#include "../supp/metal.h"
#include "../supp/dielectric.h"
#include <fcntl.h>
#include <unistd.h>

int main()
{
    t_hittable_arr *world = hittable_arr_new();

    t_material *material_ground = lambertian_new(vec3_new(0.8, 0.8, 0.0));
    t_material *material_center = lambertian_new(vec3_new(0.1, 0.2, 0.5));
    t_material *material_left = dielectric_new(1.5);
    t_material *material_bubble = dielectric_new(1.0 / 1.5);
    t_material *material_right = metal_new(vec3_new(0.8, 0.6, 0.2), 1.0);

    hittable_arr_add(world, sphere_new(vec3_new(0, -100.5, -1), 100, material_ground));
    hittable_arr_add(world, sphere_new(vec3_new(0, 0, -1.2), 0.5, material_center));
    hittable_arr_add(world, sphere_new(vec3_new(-1, 0, -1), 0.5, material_left));
    hittable_arr_add(world, sphere_new(vec3_new(-1, 0, -1), 0.4, material_bubble));
    hittable_arr_add(world, sphere_new(vec3_new(1, 0, -1), 0.5, material_right));

    int fd = open("../output/exer8_full.ppm", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    t_point3 look_from = vec3_new(-2, 2, 0);
    t_point3 look_at = vec3_new(0, 0, -1);
    t_vec3 vup = vec3_new(0, 1, 0);
    t_camera camera = camera_new_full(16.0 / 9.0, 400, 100, 50, 20, &look_from, &look_at, &vup);
    camera_render(fd, &camera, world);

    hittable_arr_free(&world);
    material_free(&material_ground);
    material_free(&material_center);
    material_free(&material_left);
    material_free(&material_right);
    close(fd);

    return 0;
}