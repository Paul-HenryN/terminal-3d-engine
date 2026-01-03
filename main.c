#include "constants.h"
#include "render.h"
#include "scene.h"
#include "shape.h"
#include "transform.h"
#include "types.h"
#include <ncurses.h>

int main(void) {
  state_t state = {.scene = new_scene(), .tool = TRANSLATE};
  scene_t *scene = &state.scene;

  scene_add_shape(scene, create_cube(0, -4, 0, 3));
  scene_add_shape(scene, create_sphere(0, 0, 0, 2, 6, 6));
  scene_add_shape(scene, create_pyramid(0, 4, 0, 4, 4));

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  render_scene(scene);
  render_menu(&state);
  refresh();

  int input = 0;
  while ((input = getch()) != 'e') {
    shape_t *curr_shape = &scene->shapes[scene->curr_shape_idx];

    switch (input) {
    case KEY_LEFT:
      scene_select_prev_shape(scene);
      break;
    case KEY_RIGHT:
      scene_select_next_shape(scene);
      break;
    case 'l':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_y(curr_shape, &curr_shape->center, -ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_x(curr_shape, TRANSLATE_INCR);
        break;
      default:
        break;
      }
      break;
    case 'j':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_y(curr_shape, &curr_shape->center, ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_x(curr_shape, -TRANSLATE_INCR);
        break;
      default:
        break;
      }
      break;
    case 'i':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_x(curr_shape, &curr_shape->center, -ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_y(curr_shape, TRANSLATE_INCR);
        break;
      default:
        break;
      }
      break;
    case 'k':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_x(curr_shape, &curr_shape->center, ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_y(curr_shape, -TRANSLATE_INCR);
        break;
      default:
        break;
      }
      break;
    case 'q':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_z(curr_shape, &curr_shape->center, ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_z(curr_shape, TRANSLATE_INCR);
        break;
      }
      break;
    case 'd':
      switch (state.tool) {
      case ROTATE:
        rotate_shape_z(curr_shape, &curr_shape->center, -ROTATE_INCR);
        break;
      case TRANSLATE:
        translate_shape_z(curr_shape, -TRANSLATE_INCR);
        break;
      }
      break;
    case 'R':
      state.tool = ROTATE;
      break;
    case 'T':
      state.tool = TRANSLATE;
      break;
    default:
      break;
    }

    clear();
    render_scene(scene);
    render_menu(&state);
    refresh();
  }

  free_scene(scene);

  endwin();
  return 0;
}
