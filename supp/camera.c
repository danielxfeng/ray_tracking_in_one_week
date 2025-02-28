#include "proj.h"
#include "camera.h"
#include "color.h"

t_camera camera_new(float aspect_ratio, float image_width)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = 1;

    return camera;
}

t_camera camera_new_aa(float aspect_ratio, float image_width, int samples_per_pixel)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = samples_per_pixel;

    return camera;
}

static void camera_init(t_camera *camera)
{
    camera->image_height = (int)(camera->image_width / camera->aspect_ratio);
    camera->camera_center = vec3_new(0, 0, 0);
    camera->pixel_samples_scale = 1.0 / (float)camera->samples_per_pixel;

    // Determine viewport dimensions.
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = camera->aspect_ratio * viewport_height;

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewpoint_u = vec3_new(viewport_width, 0, 0);
    t_vec3 viewpoint_v = vec3_new(0, viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera->pixel_delta_u = vec3_div_vec(&viewpoint_u, (float)camera->image_width);
    camera->pixel_delta_v = vec3_div_vec(&viewpoint_v, (float)camera->image_height);

    // Viewpoint top left
    // viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    t_point3 temp = vec3_new(0, 0, focal_length);
    t_point3 viewpoint_top_left = vec3_sub_vecs(&camera->camera_center, &temp);
    temp = vec3_div_vec(&viewpoint_u, 2);
    viewpoint_top_left = vec3_sub_vecs(&viewpoint_top_left, &temp);
    temp = vec3_div_vec(&viewpoint_v, 2);
    viewpoint_top_left = vec3_add_vecs(&viewpoint_top_left, &temp);

    // Pixel 100 location
    // viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    temp = vec3_add_vecs(&camera->pixel_delta_u, &camera->pixel_delta_v);
    temp = vec3_mul_vec(&temp, 0.5);
    camera->pixel00_loc = vec3_add_vecs(&viewpoint_top_left, &temp);
}

static t_color ray_color(t_ray *ray, t_hittable_arr *world)
{
    t_hit_record rec;

    t_interval interval = {0, INFINITY};
    if (hittable_arr_hit(world, ray, &interval, &rec))
    {
        t_color black = vec3_new(1, 1, 1);
        t_vec3 temp = vec3_add_vecs(&rec.normal, &black);
        return vec3_mul_vec(&temp, 0.5);
    }

    t_vec3 unit_direction = vec3_unit(ray->direction);
    float a = 0.5 * (unit_direction.y + 1.0);
    t_color white = vec3_new(1.0, 1.0, 1.0);
    t_color blue = vec3_new(0.5, 0.7, 1.0);
    t_color temp2 = vec3_mul_vec(&white, 1.0 - a);
    t_color temp3 = vec3_mul_vec(&blue, a);
    t_color res = vec3_add_vecs(&temp2, &temp3);
    return res;
}

static t_vec3 sample_square()
{
    t_vec3 vec = vec3_new(RANDOM_FLOAT - 0.5, RANDOM_FLOAT - 0.5, 0);
    return vec;
}

static t_ray *camera_get_ray(t_camera *camera, int i, int j)
{
    t_vec3 offset = sample_square();
    t_vec3 temp = vec3_mul_vec(&camera->pixel_delta_u, (float)i + offset.x);
    t_vec3 temp2 = vec3_mul_vec(&camera->pixel_delta_v, (float)j + offset.y);
    t_vec3 pixel_sample = vec3_add_vecs(&camera->pixel00_loc, &temp);
    pixel_sample = vec3_sub_vecs(&pixel_sample, &temp2);
    t_vec3 direction = vec3_sub_vecs(&pixel_sample, &camera->camera_center);
    t_ray *ray = ray_new(&camera->camera_center, &direction);
    return ray;
}

void camera_render(int fd, t_camera *camera, t_hittable_arr *world)
{
    camera_init(camera);

    dprintf(fd, "P3\n%d %d\n255\n", camera->image_width, camera->image_height);
    for (int j = 0; j < camera->image_height; ++j)
    {
        printf("Lines remaining: %d\n", camera->image_height - j);
        for (int i = 0; i < camera->image_width; ++i)
        {
            t_color pixel_color = vec3_new(0, 0, 0);
            for (int s = 0; s < camera->samples_per_pixel; ++s)
            {
                t_ray *r = camera_get_ray(camera, i, j);
                t_color r_color = ray_color(r, world);
                vec3_self_add(&pixel_color, &r_color);
                ray_free(&r);
            }
            t_color res = vec3_mul_vec(&pixel_color, camera->pixel_samples_scale);
            write_color(fd, &res);
        }
    }
    printf("Done\n");
    return;
}
