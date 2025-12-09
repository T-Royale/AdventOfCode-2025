#include "../clibs.h"

#define MAX_FRESH_INGREDIENT_RANGES 256

typedef struct ingredient_range_t {
    uint64_t min;
    uint64_t max;
} ingredient_range_t;