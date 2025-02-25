#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#define MAX_COLOR 256

typedef t_vec3 t_color;

// @brief write the color value to file.
// The color is written as integers in the range 0 to 255.
//
// @param fd: file descriptor.
// @param pixel_color: color to write, between 0 and 1.
void write_color(int fd, t_color *pixel_color);

#endif