#ifndef CAMERA_H
#define CAMERA_H

#include "hittable_arr.h"

typedef struct s_camera
{
    int image_width;
    float aspect_ratio;
    int samples_per_pixel;

    int image_height;
    float pixel_samples_scale;
    t_point3 camera_center;
    t_point3 pixel00_loc;
    t_vec3 pixel_delta_u;
    t_vec3 pixel_delta_v;
} t_camera;

t_camera camera_new(float aspect_ratio, float image_width);
t_camera camera_new_aa(float aspect_ratio, float image_width, int samples_per_pixel);
void camera_render(int fd, t_camera *camera, t_hittable_arr *world);

#endif