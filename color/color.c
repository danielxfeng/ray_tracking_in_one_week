#include "color.h"
#include <stdio.h>

void write_color(int fd, t_color *pixel_color)
{
    dprintf(fd, "%d %d %d\n",
        MAX_COLOR * pixel_color->x,
        MAX_COLOR * pixel_color->y,
        MAX_COLOR * pixel_color->z);
}
