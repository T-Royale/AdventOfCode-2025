#include "day6.h"

int main(void) {
    FILE* input = fopen("input.txt", "r");
    uint64_t result = 0;
    char lines[MAX_NUMBERS_PER_COL+1][4092];
    int lines_count = 0;
    while(fgets(lines[lines_count], 4092, input) != 0) lines_count++;
    lines_count -= 1;
    int len = strlen(lines[0]);

    uint64_t block_result = 0;
    char current_op = 0;
    bool has_block = false;

    for(int i = 0; i < len; i++){        
        int value = get_value(i, lines, lines_count);
        if(lines[lines_count][i] == '+' || lines[lines_count][i] == '*'){
            if(has_block) result += block_result;
            current_op = lines[lines_count][i];
            block_result = (current_op == '*') ? 1 : 0;
            has_block = true;
        }
        if(value == -1 || !has_block) continue;
        switch(current_op){
            case '+':
                block_result += value;
                break;
            case '*':
                block_result *= value;
                break;
            default:
                printf("INVALID OP\n");
                break;
        }
    }
    result += block_result;
    printf("El resultado final es %" PRIu64 "\n", result);
    fclose(input);
    return 0;
}

int get_value(int col, char lines[MAX_NUMBERS_PER_COL+1][4092], int lines_count){
    bool empty = true;
    char buff[lines_count+1];
    int pos = 0;
    for(int i = 0; i < lines_count; i++){
        char c = lines[i][col];
        if(!isspace((unsigned char)c)){
            buff[pos++] = c;
            empty = false;
        };
    }
    buff[pos] = '\0';
    if(empty) return -1;
    return atoi(buff);
}