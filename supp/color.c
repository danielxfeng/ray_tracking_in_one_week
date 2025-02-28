#include "color.h"
#include "interval.h"
#include <stdio.h>

void write_color(int fd, t_color *pixel_color)
{
    t_interval interval = {0.0, 0.999};

    dprintf(fd, "%d %d %d\n",
        (int)(MAX_COLOR * interval_clamp(&interval, pixel_color->x)),
        (int)(MAX_COLOR * interval_clamp(&interval, pixel_color->y)),
        (int)(MAX_COLOR * interval_clamp(&interval, pixel_color->z)));
}
