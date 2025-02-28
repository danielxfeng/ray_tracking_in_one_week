#ifndef PROJ_H
#define PROJ_H

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


# define PI (float)3.14159265358979323846
# define DTR(degrees) (degrees * M_PI / 180.0)
# define RANDOM_FLOAT (float)rand() / (float)(RAND_MAX + 1.0)
# define RANDOM_FLOAT_RANGE(min, max) (float)(min + (max - min) * RANDOM_FLOAT)

#endif