#include "render.h"
#include "constants.h"
#include "types.h"
#include <ncurses.h>
#include <stdlib.h>

void screen_yx(const point_t *point, int *screen_y, int *screen_x) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  point_t camera_pos = {0, 0, 10};
  float fov = 10.0;

  float z_relative = camera_pos.z - point->z;

  *screen_y = -1 * SCALE_FACTOR * fov * (point->y - camera_pos.y) / z_relative +
              max_y / 2;
  *screen_x = 2 * SCALE_FACTOR * fov * (point->x - camera_pos.x) / z_relative +
              max_x / 2;
}
char *tool_text(tool_t tool) {
  switch (tool) {
  case ROTATE:
    return "(R) ROTATE";
  case TRANSLATE:
    return "(T) TRANSLATE";
  default:
    return "";
  }
}

void render_shape(const shape_t *shape) {
  for (int i = 0; i < shape->nedges; i++) {
    edge_t *edge = shape->edges + i;

    int p1x, p1y, p2x, p2y;
    screen_yx(edge->p1, &p1y, &p1x);
    screen_yx(edge->p2, &p2y, &p2x);

    int dx = abs(p2x - p1x);
    int dy = abs(p2y - p1y);
    int step_x = p1x < p2x ? 1 : -1;
    int step_y = p1y < p2y ? 1 : -1;
    int error = dx - dy;

    while (p1x != p2x || p1y != p2y) {
      mvaddch(p1y, p1x, '.');
      int error2 = 2 * error;

      if (error2 > -dy) {
        error -= dy;
        p1x += step_x;
      }

      if (error2 < dx) {
        error += dx;
        p1y += step_y;
      }
    }
  }

  for (int i = 0; i < shape->npoints; i++) {
    point_t *point = shape->points + i;
    int y, x;
    screen_yx(point, &y, &x);

    mvaddch(y, x, '#');
  }
}
void render_scene(const scene_t *scene) {
  for (int i = 0; i < scene->nshapes; i++) {
    if (i == scene->curr_shape_idx) {
      attron(COLOR_PAIR(1));
    }
    render_shape(&scene->shapes[i]);
    attroff(COLOR_PAIR(1));
  }
}
void render_menu(const state_t *state) {
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  attron(A_REVERSE);
  for (int x = 0; x < max_x; x++) {
    mvaddch(max_y - 1, x, ' ');
  }

  tool_t tools[] = {ROTATE, TRANSLATE};
  int size = sizeof(tools) / sizeof(tool_t);

  move(max_y - 1, 1);
  for (int i = 0; i < size; i++) {
    int is_curr_tool = tools[i] == state->tool;

    if (is_curr_tool)
      attron(A_BOLD);
    printw("%s", tool_text(tools[i]));
    if (is_curr_tool)
      addch('*');

    attroff(A_BOLD);

    addch('\t');
  }

  attroff(A_REVERSE);
}
