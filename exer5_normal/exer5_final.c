#include "../supp/proj.h"
#include "../supp/camera.h"
#include "../supp/sphere.h"
#include <fcntl.h>
#include <unistd.h>

int main()
{
    t_hittable_arr *world = hittable_arr_new();
    hittable_arr_add(world, sphere_new(vec3_new(0, 0, -1), 0.5));
    hittable_arr_add(world, sphere_new(vec3_new(0, -100.5, -1), 100));

    int fd = open("../output/exer5_final.ppm", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    t_camera camera = camera_new(16.0 / 9.0, 400);
    camera_render(fd, &camera, world);

    hittable_arr_free(&world);
    close(fd);

    return 0;
}