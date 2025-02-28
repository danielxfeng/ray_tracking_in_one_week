#ifndef INTERVAL_H
#define INTERVAL_H

#include <math.h>
#include <stdbool.h>

typedef struct s_interval {
    float min;
    float max;
} t_interval;

extern t_interval g_empty;
extern t_interval g_universe;

float interval_size(t_interval *interval);
bool interval_contains(t_interval *interval, float value);
bool interval_surrounds(t_interval *interval, float value);

#endif
