#ifndef HITTABLE_ARR_H
#define HITTABLE_ARR_H

# include "hittable.h"

typedef struct s_hittable_arr
{
    t_hittable **arr;
    int size;
    int capacity;
} t_hittable_arr;

#endif