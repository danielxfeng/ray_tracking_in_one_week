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

    float R = cosf(M_PI / 4);

    t_material *material_left= lambertian_new(vec3_new(0, 0, 1));
    t_material *material_right = lambertian_new(vec3_new(1, 0, 0));

    hittable_arr_add(world, sphere_new(vec3_new(-R, 0, -1), R, material_left));
    hittable_arr_add(world, sphere_new(vec3_new(R, 0, -1), R, material_right));

    int fd = open("../output/exer8_camera.ppm", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    t_camera camera = camera_new_aa_depth(16.0 / 9.0, 400, 100, 50);
    camera.vfov = 90;
    camera_render(fd, &camera, world);

    hittable_arr_free(&world);
    material_free(&material_left);
    material_free(&material_right);
    close(fd);

    return 0;
}