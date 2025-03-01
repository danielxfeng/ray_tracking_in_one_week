#include "material.h"

void material_free(t_material **material)
{
    if (!material || !*material)
        return;
    free(*material);
    *material = NULL;
}