#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

typedef t_material t_dielectric;

t_material *dielectric_new(float ref_idx);

#endif