#pragma once
#include "types.h"

scene_t new_scene(void);
void free_scene(scene_t *scene);
void scene_add_shape(scene_t *scene, shape_t shape);
void scene_select_next_shape(scene_t *scene);
void scene_select_prev_shape(scene_t *scene);
