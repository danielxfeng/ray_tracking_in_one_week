#include "hittable_arr.h"

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
    arr->arr = malloc(sizeof(t_hittable *) * arr->capacity);
    if (!arr->arr)
    {
        hittable_arr_free(&arr);
        perror("malloc");
        exit(1);
    }
    return arr;
}

void hittable_arr_free(t_hittable_arr **arr)
{
    if (arr || *arr)
    {
        if ((*arr)->arr)
        {
            for (int i = 0; i < (*arr)->size; ++i)
            {
                free((*arr)->arr[i]);
                (*arr)->arr[i] = NULL;
            }
            free((*arr)->arr);
            (*arr)->arr = NULL;
        }
        free(*arr);
        *arr = NULL;
    }
}

void hittable_arr_add(t_hittable_arr *arr, t_hittable *hittable)
{
    if (arr->size == arr->capacity)
    {
        arr->capacity *= 2;
        arr->arr = realloc(arr->arr, sizeof(t_hittable *) * arr->capacity);
        if (!arr->arr)
        {
            perror("realloc");
            exit(1);
        }
    }
    arr->arr[arr->size] = hittable;
    arr->size++;
}

bool hittable_arr_hit(t_hittable_arr *arr, t_ray *r, t_interval *interval, t_hit_record *rec)
{
    t_hit_record temp_rec;
    bool hit_anything = false;
    t_interval temp_interval;
    temp_interval.min = interval->min;
    temp_interval.max = interval->max;
    for (int i = 0; i < arr->size; ++i)
    {
        if (arr->arr[i]->hit(arr->arr[i], r, &temp_interval, &temp_rec))
        {
            hit_anything = true;
            temp_interval.max = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}
