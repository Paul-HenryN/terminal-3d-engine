#include "transform.h"
#include "types.h"
#include <math.h>

void translate_x(point_t *point, float dx) { point->x += dx; }
void translate_y(point_t *point, float dy) { point->y += dy; }
void translate_z(point_t *point, float dz) { point->z += dz; }
void translate_shape_x(shape_t *shape, float dx)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    translate_x(shape->points + i, dx);
  }
  translate_x(&shape->center, dx);
}
void translate_shape_y(shape_t *shape, float dy)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    translate_y(shape->points + i, dy);
  }
  translate_y(&shape->center, dy);
}
void translate_shape_z(shape_t *shape, float dz)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    translate_z(shape->points + i, dz);
  }
  translate_z(&shape->center, dz);
}

void rotate_y(point_t *point, const point_t *center, double angle)
{
  float x = point->x - center->x;
  float z = point->z - center->z;

  point->x = x * cos(angle) + z * sin(angle);
  point->z = -1 * x * sin(angle) + z * cos(angle);

  point->x += center->x;
  point->z += center->z;
}
void rotate_x(point_t *point, const point_t *center, double angle)
{
  float y = point->y - center->y;
  float z = point->z - center->z;

  point->y = y * cos(angle) - z * sin(angle);
  point->z = y * sin(angle) + z * cos(angle);

  point->y += center->y;
  point->z += center->z;
}
void rotate_z(point_t *point, const point_t *center, double angle)
{
  float x = point->x - center->x;
  float y = point->y - center->y;

  point->x = x * cos(angle) - y * sin(angle);
  point->y = x * sin(angle) + y * cos(angle);

  point->x += center->x;
  point->y += center->y;
}
void rotate_shape_y(shape_t *shape, const point_t *center, double angle)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    rotate_y(&shape->points[i], center, angle);
  }
  if (center != &shape->center)
  {
    rotate_y(&shape->center, center, angle);
  }
}
void rotate_shape_x(shape_t *shape, const point_t *center, double angle)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    rotate_x(&shape->points[i], center, angle);
  }
  if (center != &shape->center)
  {
    rotate_x(&shape->center, center, angle);
  }
}
void rotate_shape_z(shape_t *shape, const point_t *center, double angle)
{
  for (int i = 0; i < shape->npoints; i++)
  {
    rotate_z(&shape->points[i], center, angle);
  }
  if (center != &shape->center)
  {
    rotate_z(&shape->center, center, angle);
  }
}
