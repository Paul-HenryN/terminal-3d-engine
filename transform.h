#include "types.h"

void translate_x(point_t *point, float dx);
void translate_y(point_t *point, float dy);
void translate_z(point_t *point, float dz);
void translate_shape_x(shape_t *shape, float dx);
void translate_shape_y(shape_t *shape, float dy);
void translate_shape_z(shape_t *shape, float dz);

void rotate_y(point_t *point, const point_t *center, double angle);
void rotate_x(point_t *point, const point_t *center, double angle);
void rotate_z(point_t *point, const point_t *center, double angle);
void rotate_shape_y(shape_t *shape, const point_t *center, double angle);
void rotate_shape_x(shape_t *shape, const point_t *center, double angle);
void rotate_shape_z(shape_t *shape, const point_t *center, double angle);
