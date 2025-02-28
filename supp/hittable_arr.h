#ifndef HITTABLE_ARR_H
#define HITTABLE_ARR_H

# include "hittable.h"

typedef struct s_hittable_arr
{
    t_hittable **arr;
    int size;
    int capacity;
} t_hittable_arr;

t_hittable_arr *hittable_arr_new();
void hittable_arr_free(t_hittable_arr **arr);
void hittable_arr_add(t_hittable_arr *arr, t_hittable *hittable);
bool hittable_arr_hit(t_hittable_arr *arr, t_ray *r, float t_min, float t_max, t_hit_record *rec);

#endif