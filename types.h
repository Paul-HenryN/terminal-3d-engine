#pragma once

typedef enum
{
    ROTATE,
    TRANSLATE
} tool_t;

typedef struct
{
    float x;
    float y;
    float z;
} point_t;

typedef struct
{
    point_t *p1;
    point_t *p2;
} edge_t;

typedef struct
{
    point_t *points;
    point_t center;
    edge_t *edges;
    int npoints;
    int nedges;
} shape_t;

typedef struct
{
    shape_t *shapes;
    int nshapes;
    int curr_shape_idx;
} scene_t;

typedef struct
{
    scene_t scene;
    tool_t tool;
} state_t;
