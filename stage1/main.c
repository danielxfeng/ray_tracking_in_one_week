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

    t_material *material_ground = lambertian_new(vec3_new(0.5, 0.5, 0.5));

    hittable_arr_add(world, sphere_new(vec3_new(0, -1000, 0), 1000, material_ground));

    t_material *materials[1000];

    int i = 0;
    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            float choose_mat = RANDOM_FLOAT;
            t_point3 center = vec3_new(a + 0.9 * RANDOM_FLOAT, 0.2, b + 0.9 * RANDOM_FLOAT);

            t_vec3 new = vec3_new(4, 0.2, 0);
            t_vec3 offset = vec3_sub_vecs(&center, &new);
            if (vec3_length(&offset) > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    // diffuse
                    t_vec3 temp1 = vec3_random();
                    t_vec3 temp2 = vec3_random();
                    t_vec3 albedo = vec3_mul_vecs(&temp1, &temp2);
                    materials[i] = lambertian_new(albedo);
                    hittable_arr_add(world, sphere_new(center, 0.2, materials[i]));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    t_vec3 albedo = vec3_random_range(0.5, 1);
                    float fuzz = RANDOM_FLOAT_RANGE(0, 0.5);
                    materials[i] = metal_new(albedo, fuzz);
                    hittable_arr_add(world, sphere_new(center, 0.2, materials[i]));
                }
                else
                {
                    // glass
                    materials[i] = dielectric_new(1.5);
                    hittable_arr_add(world, sphere_new(center, 0.2, materials[i]));
                }
                ++i;
            }
        }
    }

    t_material *material1 = dielectric_new(1.5);
    hittable_arr_add(world, sphere_new(vec3_new(0, 1, 0), 1.0, material1));
    t_material *material2 = lambertian_new(vec3_new(0.4, 0.2, 0.1));
    hittable_arr_add(world, sphere_new(vec3_new(-4, 1, 0), 1.0, material2));
    t_material *material3 = metal_new(vec3_new(0.7, 0.6, 0.5), 0.0);
    hittable_arr_add(world, sphere_new(vec3_new(4, 1, 0), 1.0, material3));

    t_point3 look_from = vec3_new(13, 2, 3);
    t_point3 look_at = vec3_new(0, 0, 0);
    t_vec3 vup = vec3_new(0, 1, 0);
    t_camera camera = camera_new_full(16.0 / 9.0, 1200, 10, 50, 20, &look_from, &look_at, &vup);
    camera.defocus_angle = 0;
    camera.focus_dist = 10;

    int fd = open("../output/rt_in_weekend.ppm", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    camera_render(fd, &camera, world);

    hittable_arr_free(&world);
    material_free(&material_ground);
    material_free(&material1);
    material_free(&material2);
    material_free(&material3);

    for (int j = 0; j < i; ++j)
        material_free(&materials[j]);
    close(fd);

    exit(0);
}
