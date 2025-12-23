#pragma once
#include "../clibs.h"
#include <math.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MAX_SQUARE_COUNT 500
#define MAX_LINE_LEN 16

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int x1, y1;
    int x2, y2;
} segment_t;

typedef struct {
    int l, r;
} interval_t;

typedef struct {
    int row;
    int count;
    interval_t* intervals;
} row_t;

int sort_elements(const void* p1, const void* p2);
bool rectangle_is_valid(int xL, int xR, int yB, int yT, row_t* rows, int y_min);