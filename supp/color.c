#include "color.h"
#include "interval.h"
#include <stdio.h>
#include <math.h>

static float linear_to_gamma(float linear)
{
    if (linear <= 0.0)
        return 0.0;
    return sqrtf(linear);
}

void write_color(int fd, t_color *pixel_color)
{
    t_interval interval = {0.0, 0.999};

    dprintf(fd, "%d %d %d\n",
        (int)(MAX_COLOR * interval_clamp(&interval, linear_to_gamma(pixel_color->x))),
        (int)(MAX_COLOR * interval_clamp(&interval, linear_to_gamma(pixel_color->y))),
        (int)(MAX_COLOR * interval_clamp(&interval, linear_to_gamma(pixel_color->z))));
}
