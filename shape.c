#include "shape.h"
#include "types.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

shape_t create_sphere(float cy, float cx, float cz, float radius, int lat_rings,
                      int lon_rings) {
  const int npoints = (lat_rings - 1) * lon_rings + 2;
  // Edges: horizontal rings + vertical lines + pole connections
  const int horizontal_edges = (lat_rings - 1) * lon_rings;
  const int vertical_edges = (lat_rings - 2) * lon_rings;
  const int pole_edges = lon_rings * 2;
  const int nedges = horizontal_edges + vertical_edges + pole_edges;

  point_t *points = malloc(npoints * sizeof(point_t));
  if (points == NULL) {
    perror("sphere points malloc");
    exit(EXIT_FAILURE);
  }

  edge_t *edges = malloc(nedges * sizeof(edge_t));
  if (edges == NULL) {
    perror("sphere edges malloc");
    exit(EXIT_FAILURE);
  }

  shape_t sphere = {.points = points,
                    .edges = edges,
                    .center = (point_t){cx, cy, cz},
                    .npoints = npoints,
                    .nedges = nedges};

  // North pole (index 0) and south pole (index npoints - 1)
  sphere.points[0] = (point_t){cx, cy + radius, cz};
  sphere.points[npoints - 1] = (point_t){cx, cy - radius, cz};

  // Generate middle ring points
  // Points are stored: [north_pole, ring1_lon0, ring1_lon1, ..., ring2_lon0,
  // ..., south_pole]
  int point_idx = 1;

  for (int lat = 1; lat < lat_rings; lat++) {
    float theta = lat * (M_PI / lat_rings);

    for (int lon = 0; lon < lon_rings; lon++) {
      float phi = lon * (2 * M_PI / lon_rings);

      sphere.points[point_idx] =
          (point_t){.x = cx + radius * sin(theta) * cos(phi),
                    .y = cy + radius * cos(theta),
                    .z = cz + radius * sin(theta) * sin(phi)};

      point_idx++;
    }
  }

  // Generate edges
  int edge_idx = 0;

// Helper to get point index for a given lat ring and lon position
// lat=0 means first ring (after north pole), lat=lat_rings-2 means last ring
// (before south pole)
#define RING_POINT(lat, lon) (1 + (lat) * lon_rings + (lon))

  // Horizontal edges (around each latitude ring)
  for (int lat = 0; lat < lat_rings - 1; lat++) {
    for (int lon = 0; lon < lon_rings; lon++) {
      int next_lon = (lon + 1) % lon_rings;
      sphere.edges[edge_idx++] =
          (edge_t){&sphere.points[RING_POINT(lat, lon)],
                   &sphere.points[RING_POINT(lat, next_lon)]};
    }
  }

  // Vertical edges (connecting adjacent latitude rings)
  for (int lat = 0; lat < lat_rings - 2; lat++) {
    for (int lon = 0; lon < lon_rings; lon++) {
      sphere.edges[edge_idx++] =
          (edge_t){&sphere.points[RING_POINT(lat, lon)],
                   &sphere.points[RING_POINT(lat + 1, lon)]};
    }
  }

  // North pole connections (to first ring)
  for (int lon = 0; lon < lon_rings; lon++) {
    sphere.edges[edge_idx++] =
        (edge_t){&sphere.points[0], &sphere.points[RING_POINT(0, lon)]};
  }

  // South pole connections (to last ring)
  for (int lon = 0; lon < lon_rings; lon++) {
    sphere.edges[edge_idx++] =
        (edge_t){&sphere.points[npoints - 1],
                 &sphere.points[RING_POINT(lat_rings - 2, lon)]};
  }

#undef RING_POINT

  return sphere;
}
shape_t create_pyramid(float cy, float cx, float cz, float height, float base) {
  const int npoints = 5;
  const int nedges = 8;

  point_t *points = malloc(npoints * sizeof(point_t));
  if (points == NULL) {
    perror("pyramid points malloc");
    exit(EXIT_FAILURE);
  }

  edge_t *edges = malloc(nedges * sizeof(edge_t));
  if (edges == NULL) {
    perror("pyramid edges malloc");
    exit(EXIT_FAILURE);
  }

  shape_t pyramid = {.points = points,
                     .edges = edges,
                     .center = (point_t){cx, cy, cz},
                     .npoints = npoints,
                     .nedges = nedges};

  pyramid.points[0] = (point_t){cx - base / 2, cy - height / 2, cz + base / 2};
  pyramid.points[1] = (point_t){cx + base / 2, cy - height / 2, cz + base / 2};
  pyramid.points[2] = (point_t){cx - base / 2, cy - height / 2, cz - base / 2};
  pyramid.points[3] = (point_t){cx + base / 2, cy - height / 2, cz - base / 2};
  pyramid.points[4] = (point_t){cx, cy + height / 2, cz};

  pyramid.edges[0] = (edge_t){pyramid.points + 0, pyramid.points + 1};
  pyramid.edges[1] = (edge_t){pyramid.points + 0, pyramid.points + 2};
  pyramid.edges[2] = (edge_t){pyramid.points + 0, pyramid.points + 4};
  pyramid.edges[3] = (edge_t){pyramid.points + 1, pyramid.points + 3};
  pyramid.edges[4] = (edge_t){pyramid.points + 1, pyramid.points + 4};
  pyramid.edges[5] = (edge_t){pyramid.points + 2, pyramid.points + 3};
  pyramid.edges[6] = (edge_t){pyramid.points + 2, pyramid.points + 4};
  pyramid.edges[7] = (edge_t){pyramid.points + 3, pyramid.points + 4};

  return pyramid;
}
shape_t create_cube(float cy, float cx, float cz, float side) {
  const int npoints = 8;
  const int nedges = 12;

  point_t *points = malloc(npoints * sizeof(point_t));
  if (points == NULL) {
    perror("cube points malloc");
    exit(EXIT_FAILURE);
  }

  edge_t *edges = malloc(nedges * sizeof(edge_t));
  if (edges == NULL) {
    perror("cube edges malloc");
    exit(EXIT_FAILURE);
  }

  shape_t cube = {.points = points,
                  .edges = edges,
                  .center = (point_t){cx, cy, cz},
                  .npoints = npoints,
                  .nedges = nedges};

  cube.points[0] = (point_t){cx - side / 2, cy + side / 2, cz + side / 2};
  cube.points[1] = (point_t){cx + side / 2, cy + side / 2, cz + side / 2};
  cube.points[2] = (point_t){cx + side / 2, cy - side / 2, cz + side / 2};
  cube.points[3] = (point_t){cx - side / 2, cy - side / 2, cz + side / 2};
  cube.points[4] = (point_t){cx - side / 2, cy + side / 2, cz - side / 2};
  cube.points[5] = (point_t){cx + side / 2, cy + side / 2, cz - side / 2};
  cube.points[6] = (point_t){cx + side / 2, cy - side / 2, cz - side / 2};
  cube.points[7] = (point_t){cx - side / 2, cy - side / 2, cz - side / 2};

  // Front face edges
  cube.edges[0] = (edge_t){&cube.points[0], &cube.points[1]};
  cube.edges[1] = (edge_t){&cube.points[1], &cube.points[2]};
  cube.edges[2] = (edge_t){&cube.points[2], &cube.points[3]};
  cube.edges[3] = (edge_t){&cube.points[3], &cube.points[0]};
  // Back face edges
  cube.edges[4] = (edge_t){&cube.points[4], &cube.points[5]};
  cube.edges[5] = (edge_t){&cube.points[5], &cube.points[6]};
  cube.edges[6] = (edge_t){&cube.points[6], &cube.points[7]};
  cube.edges[7] = (edge_t){&cube.points[7], &cube.points[4]};
  // Connecting edges
  cube.edges[8] = (edge_t){&cube.points[0], &cube.points[4]};
  cube.edges[9] = (edge_t){&cube.points[1], &cube.points[5]};
  cube.edges[10] = (edge_t){&cube.points[2], &cube.points[6]};
  cube.edges[11] = (edge_t){&cube.points[3], &cube.points[7]};

  return cube;
}

void free_shape(shape_t *shape) {
  free(shape->points);
  free(shape->edges);
  shape->npoints = 0;
  shape->nedges = 0;
}
