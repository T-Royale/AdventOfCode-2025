#pragma once

#include "../clibs.h"

#define MAX_OPERATIONS 4092
#define NUMBERS_PER_COL 4
#define MAX_PROBLEMS 1024

typedef struct problem_t {
    uint64_t nums[NUMBERS_PER_COL];
    char op;
} problem_t;

bool is_empty(int col, char grid[][4092]);