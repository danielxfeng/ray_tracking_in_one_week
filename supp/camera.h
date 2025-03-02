#ifndef CAMERA_H
#define CAMERA_H

#include "hittable_arr.h"

typedef struct s_camera
{
    int image_width;
    float aspect_ratio;
    int samples_per_pixel;
    int max_depth;
    float vfov;
    t_point3 look_from;
    t_point3 look_at;
    t_vec3 vup;
    float defocus_angle;
    float focus_dist;

    int image_height;
    float pixel_samples_scale;
    t_point3 camera_center;
    t_point3 pixel00_loc;
    t_vec3 pixel_delta_u;
    t_vec3 pixel_delta_v;
    t_vec3 defocus_disk_u;
    t_vec3 defocus_disk_v;
    t_vec3 u, v, w;
} t_camera;

t_camera camera_new(float aspect_ratio, float image_width);
t_camera camera_new_aa(float aspect_ratio, float image_width, int samples_per_pixel);
t_camera camera_new_aa_depth(float aspect_ratio, float image_width, int samples_per_pixel, int max_depth);
t_camera camera_new_full(float aspect_ratio, float image_width, int samples_per_pixel, int max_depth, float vfov, t_point3 *look_from, t_point3 *look_at, t_vec3 *vup);
void camera_render(int fd, t_camera *camera, t_hittable_arr *world);

#endif