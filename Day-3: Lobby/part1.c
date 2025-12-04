#include "day3.h"

int main(){
    FILE* input = fopen(input_path, "r");
    char *block = calloc(MAX_BLOCK_LEN, sizeof(char));
    int result = 0;

    while(fgets(block, MAX_BLOCK_LEN, input) != NULL){
        char *null_term = strchr(block, '\n');
        if(null_term) *null_term = '\0';
        int len = strlen(block);
        int tens = 0;
        char *tens_ptr = NULL;
        char max_digit = -1;
        for(int i = len-2; i >= 0; i--){
            if(block[i] >= max_digit) {
                max_digit = block[i];
                tens_ptr = &block[i];
            }
        }
        tens = (*tens_ptr - CHARtoINT_offset) * 10;
        int units = 0;
        for(int i = (tens_ptr - block) + 1; i < len; i++){
            if(block[i] - CHARtoINT_offset > units) units = block[i] - CHARtoINT_offset;
        }
        result += tens + units;
        // printf("Block: %s gives result: %d\n", block, tens + units); // UNCOMMENT FOR TESTING
    }
    printf("Final result is: %d\n", result);
    
    fclose(input);
    free(block);
    return 0;
}