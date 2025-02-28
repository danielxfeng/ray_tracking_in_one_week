#include "interval.h"

t_interval g_empty = {INFINITY, -INFINITY};
t_interval g_universe = {-INFINITY, INFINITY};

float interval_size(t_interval *interval)
{
    return interval->max - interval->min;
}

bool interval_contains(t_interval *interval, float value)
{
    return value >= interval->min && value <= interval->max;
}

bool interval_surrounds(t_interval *interval, float value)
{
    return value > interval->min && value < interval->max;
}

float interval_clamp(t_interval *interval, float value)
{
    if (value < interval->min)
        return interval->min;
    if (value > interval->max)
        return interval->max;
    return value;
}