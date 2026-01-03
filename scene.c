#include "scene.h"
#include "shape.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

scene_t new_scene(void) {
  return (scene_t){.shapes = NULL, .nshapes = 0, .curr_shape_idx = -1};
}
void free_scene(scene_t *scene) {
  for (int i = 0; i < scene->nshapes; i++) {
    free_shape(&scene->shapes[i]);
  }
  free(scene->shapes);
  scene->nshapes = 0;
  scene->curr_shape_idx = -1;
}

void scene_add_shape(scene_t *scene, shape_t shape) {
  shape_t *new_shapes =
      realloc(scene->shapes, (scene->nshapes + 1) * sizeof(shape_t));

  if (new_shapes == NULL) {
    perror("scene_add_shape realloc");
    exit(EXIT_FAILURE);
  }

  scene->shapes = new_shapes;
  scene->nshapes++;
  scene->shapes[scene->nshapes - 1] = shape;

  if (scene->nshapes == 1) {
    scene->curr_shape_idx = 0;
  }
}

void scene_select_next_shape(scene_t *scene) {
  if (scene->nshapes == 0) {
    return;
  }

  if (scene->curr_shape_idx < scene->nshapes - 1) {
    scene->curr_shape_idx++;
  } else {
    scene->curr_shape_idx = 0;
  }
}

void scene_select_prev_shape(scene_t *scene) {
  if (scene->nshapes == 0) {
    return;
  }

  if (scene->curr_shape_idx > 0) {
    scene->curr_shape_idx--;
  } else {
    scene->curr_shape_idx = scene->nshapes - 1;
  }
}
