#include "day5.h"

int main(void) {
    FILE* input = fopen("input.txt", "r");
    char line[128];
    unsigned int range_count = 0;
    ingredient_range_t* ranges = calloc(MAX_FRESH_INGREDIENT_RANGES, sizeof(ingredient_range_t));
    bool input_is_ranges = true;
    int result = 0;
    while(fgets(line, 128, input)){
        if(input_is_ranges){
            if(sscanf(line, "%" SCNu64 "-%" SCNu64, &ranges[range_count].min, &ranges[range_count].max) != 2) {
                input_is_ranges = false;
                continue;
            }
            range_count++;
        }
        else {
            uint64_t id;
            sscanf(line, "%" SCNu64, &id);
            for(int i = 0; i < range_count; i++){
                if(id >= ranges[i].min && id <= ranges[i].max) {
                    result++;
                    // printf("Number %" SCNu64 " is included in range %" SCNu64 " to %" SCNu64 "\n", id, ranges[i].min, ranges[i].max);
                    break;
                }
            }
        }
    }
    free(ranges);
    printf("Result is: %d\n", result);
    return 0;
}