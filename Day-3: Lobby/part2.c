#include "day3.h"

const int TOTAL_BATTERY_COUNT = 12;

int main(){
    FILE* input = fopen(input_path, "r");
    char *block = calloc(MAX_BLOCK_LEN, sizeof(char));
    uint64_t result = 0;
    char *block_result_str = calloc(TOTAL_BATTERY_COUNT + 1, sizeof(char));

    while(fgets(block, MAX_BLOCK_LEN, input) != NULL){
        char *null_term = strchr(block, '\n');
        if(null_term) *null_term = '\0';
        int len = strlen(block);
        if(len < 13) return 0;

        int range_min = 0;
        for(int i = 0; i < TOTAL_BATTERY_COUNT; i++){
            int max = 0;
            for(int j = range_min; j <= len - (TOTAL_BATTERY_COUNT - i); j++){
                if(block[j] > max){
                    max = block[j];
                    range_min = j+1; 
                }
            }
            block_result_str[i] = (char)max;
        }

        char *end;
        uint64_t block_result = strtoll(block_result_str, &end, 10);
        result += block_result;
        // printf("Block: %s gives result: %s\n", block, block_result_str); // UNCOMMENT FOR TESTING
    }
    printf("Final result is: %" PRIu64 "\n", result);
    
    fclose(input);
    free(block);
    return 0;
}