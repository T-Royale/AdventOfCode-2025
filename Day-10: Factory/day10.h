#pragma once
#include "../clibs.h"

typedef unsigned int diagram_t;

#include <math.h>

#define MAX_LINE_LEN 256
#define INITIAL_STATE 0
#define MAX_BUTTONS 16
#define MAX_STEPS 256 // Timeout for debugging purposes

typedef struct {
    unsigned int count;
    diagram_t value[MAX_BUTTONS]; 
} buttons_t;

int min_steps(diagram_t target, buttons_t *buttons, uint64_t lights_count);