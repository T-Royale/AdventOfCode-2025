#include "day5.h"

int main(void) {
    FILE* input = fopen("input.txt", "r");
    char line[128];
    unsigned int range_count = 0;
    ingredient_range_t* ranges = calloc(MAX_FRESH_INGREDIENT_RANGES, sizeof(ingredient_range_t));
    uint64_t result = 0;
    while(fgets(line, 128, input)){
        if(sscanf(line, "%" SCNu64 "-%" SCNu64, &ranges[range_count].min, &ranges[range_count].max) != 2) {
            break;
        }
        range_count++;
    }
    qsort(ranges, range_count, sizeof(ingredient_range_t), cmp);
    uint64_t current_min = ranges[0].min;
    uint64_t current_max = ranges[0].max;

    for (unsigned int i = 1; i < range_count; i++) {
        if (ranges[i].min <= current_max + 1) {
            if (ranges[i].max > current_max) {
                current_max = ranges[i].max;
            }
        } else {
            result += current_max - current_min + 1;
            current_min = ranges[i].min;
            current_max = ranges[i].max;
        }
    }
    result += current_max - current_min + 1;

    printf("Result is: %" PRIu64 "\n", result);
    return 0;
}

int cmp(const void *a, const void *b) {
    const ingredient_range_t *r1 = (const ingredient_range_t *)a;
    const ingredient_range_t *r2 = (const ingredient_range_t *)b;

    if (r1->min < r2->min) return -1;
    if (r1->min > r2->min) return 1;
    return 0;
}