#pragma once
#include "../clibs.h"
#include <math.h>
#include <float.h>

#define MAX_BOXES_COUNT 1023
#define MAX_COORDENATE_LEN 31

typedef struct{
    long x;
    long y;
    long z;
} junction_box_t;

typedef struct {
    junction_box_t list[MAX_BOXES_COUNT];
    unsigned int count;
} junction_box_list_t;

typedef struct {
    long a;
    long b;
    double dist;
} connection_t;

double calculate_distance(junction_box_t a, junction_box_t b);
int sort_distances(const void *p0, const void *p2);

long find(long x);
int combine(long a, long b);