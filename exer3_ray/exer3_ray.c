#include "../supp/color.h"
#include "../supp/vec3.h"
#include "../supp/ray.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

t_color ray_color(t_ray *ray)
{
    t_vec3 unit_direction = vec3_unit(ray->direction);
    float t = 0.5 * (unit_direction.y + 1.0);
    t_color white = vec3_new(1.0, 1.0, 1.0);
    t_color blue = vec3_new(0.5, 0.7, 1.0);
    t_color temp1 = vec3_mul_vec(&white, 1.0 - t);
    t_color temp2 = vec3_mul_vec(&blue, t);
    return vec3_add_vecs(&temp1, &temp2);
}


int main()
{
    int fd = open("../output/exer3_ray.ppm", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    int image_width = 400;
    float aspect_ratio = 16.0 / 9.0;
    int image_height = (int)(image_width / aspect_ratio);
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;

    // Camera
    t_point3 camera_center = vec3_new(0, 0, 0);

    // Viewport
    t_vec3 viewpoint_u = vec3_new(viewport_width, 0, 0);
    t_vec3 viewpoint_v = vec3_new(0, viewport_height, 0);

    // Pixel delta
    t_vec3 pixel_delta_u = vec3_div_vec(&viewpoint_u, (float)image_width);
    t_vec3 pixel_delta_v = vec3_div_vec(&viewpoint_v, (float)image_height);
    printf("Pixel delta u: %f %f %f\n", pixel_delta_u.x, pixel_delta_u.y, pixel_delta_u.z);

    // Viewpoint top left
    // viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    t_point3 temp = vec3_new(0, 0, focal_length);
    t_point3 viewpoint_top_left = vec3_sub_vecs(&camera_center, &temp);
    temp = vec3_div_vec(&viewpoint_u, 2);
    viewpoint_top_left = vec3_sub_vecs(&viewpoint_top_left, &temp);
    temp = vec3_div_vec(&viewpoint_v, 2);
    viewpoint_top_left = vec3_add_vecs(&viewpoint_top_left, &temp);

    // Pixel 100 location
    // viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    temp = vec3_add_vecs(&pixel_delta_u, &pixel_delta_v);
    temp = vec3_mul_vec(&temp, 0.5);
    t_point3 pixel_100_loc = vec3_add_vecs(&viewpoint_top_left, &temp);

    // Render

    dprintf(fd, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j)
    {
        printf("Lines remaining: %d\n", image_height - j);
        for (int i = 0; i < image_width; ++i)
        {
            temp = vec3_mul_vec(&pixel_delta_u, (float)i);
            t_point3 temp2 = vec3_mul_vec(&pixel_delta_v, (float)j);
            t_point3 pixel_center = vec3_add_vecs(&viewpoint_top_left, &temp);
            pixel_center = vec3_sub_vecs(&pixel_center, &temp2);

            t_vec3 direction = vec3_sub_vecs(&pixel_center, &camera_center);
            t_ray *ray = ray_new(&camera_center, &direction);

            t_color pixel_color = ray_color(ray);
            write_color(fd, &pixel_color);
            ray_free(&ray);
        }
    }
    printf("Done\n");

    close(fd);
    return 0;
}
