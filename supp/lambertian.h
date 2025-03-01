#ifndef LABERTIAN_H
#define LABERTIAN_H

#include "material.h"

typedef t_material t_lambertian;

t_material *lambertian_new(t_color albedo);

#endif