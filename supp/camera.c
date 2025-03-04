#include "proj.h"
#include "camera.h"
#include "color.h"

t_camera camera_new(float aspect_ratio, float image_width)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = 1;
    camera.max_depth = 10000;

    return camera;
}

t_camera camera_new_aa(float aspect_ratio, float image_width, int samples_per_pixel)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = samples_per_pixel;
    camera.max_depth = 10000;
    camera.vfov = 90;
    camera.look_from = vec3_new(0, 0, 0);
    camera.look_at = vec3_new(0, 0, -1);
    camera.vup = vec3_new(0, 1, 0);

    return camera;
}

t_camera camera_new_aa_depth(float aspect_ratio, float image_width, int samples_per_pixel, int max_depth)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = samples_per_pixel;
    camera.max_depth = max_depth;
    camera.vfov = 90;
    camera.look_from = vec3_new(0, 0, 0);
    camera.look_at = vec3_new(0, 0, -1);
    camera.vup = vec3_new(0, 1, 0);

    return camera;
}

t_camera camera_new_full(float aspect_ratio, float image_width, int samples_per_pixel, int max_depth, float vfov, t_point3 *look_from, t_point3 *look_at, t_vec3 *vup)
{
    t_camera camera;
    camera.image_width = image_width;
    camera.aspect_ratio = aspect_ratio;
    camera.samples_per_pixel = samples_per_pixel;
    camera.max_depth = max_depth;
    camera.vfov = vfov;
    camera.look_from = vec3_copy(look_from);
    camera.look_at = vec3_copy(look_at);
    camera.vup = vec3_copy(vup);

    return camera;
}

static void camera_init(t_camera *camera)
{
    camera->image_height = (int)(camera->image_width / camera->aspect_ratio);
    camera->camera_center = vec3_copy(&camera->look_from);
    camera->pixel_samples_scale = 1.0 / (float)camera->samples_per_pixel;

    // Determine viewport dimensions.
    t_vec3 dist = vec3_sub_vecs(&camera->look_from, &camera->look_at);
    float theta = DTR(camera->vfov);
    float h = tanf(theta / 2);
    float viewport_height = 2.0 * h * camera->focus_dist;
    float viewport_width = camera->aspect_ratio * viewport_height;

    camera->w = vec3_unit(&dist);
    t_vec3 cross = vec3_cross(&camera->vup, &camera->w);
    camera->u = vec3_unit(&cross);
    camera->v = vec3_cross(&camera->w, &camera->u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewpoint_u = vec3_mul_vec(&camera->u, viewport_width);
    t_vec3 viewpoint_v = vec3_mul_vec(&camera->v, viewport_height);
    //viewpoint_v = vec3_flip_minus(&viewpoint_v);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera->pixel_delta_u = vec3_div_vec(&viewpoint_u, (float)camera->image_width);
    camera->pixel_delta_v = vec3_div_vec(&viewpoint_v, (float)camera->image_height);

    // Viewpoint top left
    // viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // center - (focal_length * w) - viewport_u/2 - viewport_v/2
    t_vec3 focal_w = vec3_mul_vec(&camera->w, camera->focus_dist);
    t_vec3 vu2 = vec3_div_vec(&viewpoint_u, 2);
    t_vec3 vv2 = vec3_div_vec(&viewpoint_v, 2);
    t_vec3 viewpoint_top_left = vec3_sub_vecs(&camera->camera_center, &focal_w);
    viewpoint_top_left = vec3_sub_vecs(&viewpoint_top_left, &vu2);
    viewpoint_top_left = vec3_add_vecs(&viewpoint_top_left, &vv2);

    // Pixel 100 location
    // viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    t_vec3 temp = vec3_add_vecs(&camera->pixel_delta_u, &camera->pixel_delta_v);
    temp = vec3_mul_vec(&temp, 0.5);
    camera->pixel00_loc = vec3_add_vecs(&viewpoint_top_left, &temp);

    // Calculate the defocus disk basis vectors.
    float defocus_radius = camera->focus_dist * tanf(DTR(camera->defocus_angle / 2));
    camera->defocus_disk_u = vec3_mul_vec(&camera->u, defocus_radius);
    camera->defocus_disk_v = vec3_mul_vec(&camera->v, defocus_radius); 
}

static t_color ray_color(t_ray *ray, t_hittable_arr *world, int depth_left)
{
    if (depth_left <= 0)
    {
        return vec3_new(0, 0, 0);
    }

    t_hit_record rec;

    t_interval interval = {0.001, INFINITY};
    if (hittable_arr_hit(world, ray, &interval, &rec))
    {
        t_ray *scattered;
        t_color attenuation;
        if (rec.material->scatter(rec.material, ray, &rec, &attenuation, &scattered))
        {
            t_color res = ray_color(scattered, world, depth_left - 1);
            res = vec3_mul_vecs(&res, &attenuation);
            ray_free(&scattered);
            return res;
        }
        return vec3_new(0, 0, 0);
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

static t_point3 camera_defocus_disk_sample(t_camera *camera)
{
    t_vec3 p = vec3_random_in_unit_disk();
    t_vec3 temp = vec3_mul_vec(&camera->defocus_disk_u, p.x);
    t_vec3 temp2 = vec3_mul_vec(&camera->defocus_disk_v, p.y);
    t_vec3 offset = vec3_add_vecs(&temp, &temp2);
    t_point3 res = vec3_add_vecs(&camera->camera_center, &offset);
    return res;
}

static t_ray *camera_get_ray(t_camera *camera, int i, int j)
{
    t_vec3 offset = sample_square();
    t_vec3 temp = vec3_mul_vec(&camera->pixel_delta_u, (float)i + offset.x);
    t_vec3 temp2 = vec3_mul_vec(&camera->pixel_delta_v, (float)j + offset.y);
    t_vec3 pixel_sample = vec3_add_vecs(&camera->pixel00_loc, &temp);
    pixel_sample = vec3_sub_vecs(&pixel_sample, &temp2);
    t_vec3 orig = camera->defocus_angle <= 0 ? camera->camera_center : camera_defocus_disk_sample(camera);
    t_vec3 direction = vec3_sub_vecs(&pixel_sample, &camera->camera_center);
    t_ray *ray = ray_new(&orig, &direction);
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
                t_color r_color = ray_color(r, world, camera->max_depth);
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
