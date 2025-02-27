#include "hittable_arr.h"
#include <stdlib.h>

t_hittable_arr *hittable_arr_new()
{
    t_hittable_arr *arr;
    arr = calloc(1, sizeof(t_hittable_arr));
    if (!arr)
    {
        perror("calloc");
        exit(1);
    }
    arr->capacity = 16;
    arr->arr = malloc(sizeof(t_hit_record) * arr->capacity);
    if (!arr->arr)
    {
        hittable_arr_free(&arr);
        perror("malloc");
        exit(1);
    }
    return &arr;
}

void hittable_arr_free(t_hittable_arr **arr)
{
    if (arr || *arr)
    {
        free((*arr)->arr);
        (*arr)->arr = NULL;
        free(*arr);
        *arr = NULL;
    }
}

void hittable_arr_add(t_hittable_arr *arr, t_hit_record *rec)
{
    if (arr->size == arr->capacity)
    {
        arr->capacity *= 2;
        arr->arr = realloc(arr->arr, sizeof(t_hit_record) * arr->capacity);
        if (!arr->arr)
        {
            perror("realloc");
            exit(1);
        }
    }
    arr->arr[arr->size] = *rec;
    arr->size++;
    return true;
}

bool hittable_arr_hit(t_hittable_arr *arr, t_ray *r, float t_min, float t_max)
{
    for (int i = 0; i < arr->size; ++i)
    {
        if (arr->arr[i].hit(&arr->arr[i], r, t_min, t_max))
            return true;
    }
    return false;
}
