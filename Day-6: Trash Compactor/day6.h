#pragma once

#include "../clibs.h"
#include <ctype.h>

#define MAX_OPERATIONS 4092
#define MAX_NUMBERS_PER_COL 4
#define MAX_PROBLEMS 1024

typedef struct problem_t {
    uint64_t *nums;
    char op;
} problem_t;

int get_value(int col, char lines[MAX_NUMBERS_PER_COL+1][4092], int lines_count);