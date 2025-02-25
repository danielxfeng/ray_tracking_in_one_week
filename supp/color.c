#include "color.h"
#include <stdio.h>

void write_color(int fd, t_color *pixel_color)
{
    dprintf(fd, "%d %d %d\n",
        (int)(MAX_COLOR * pixel_color->x),
        (int)(MAX_COLOR * pixel_color->y),
        (int)(MAX_COLOR * pixel_color->z));
}
