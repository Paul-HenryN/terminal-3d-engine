#pragma once
#include "types.h"

shape_t create_sphere(float cy, float cx, float cz, float radius, int lat_rings,
                      int lon_rings);
shape_t create_pyramid(float cy, float cx, float cz, float height, float base);
shape_t create_cube(float cy, float cx, float cz, float side);
void free_shape(shape_t *shape);
