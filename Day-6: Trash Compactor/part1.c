#include "day6.h"

int main(void) {
    FILE* input = fopen("input.txt", "r");
    uint64_t result = 0;
    char lines[MAX_NUMBERS_PER_COL+1][4092];
    int lines_count = 0;
    while(fgets(lines[lines_count], 4092, input) != 0) lines_count++;
    lines_count -= 1;
    for(int i = 0; i <= lines_count; i++) fgets(lines[i], 4092, input);
    int len = strlen(lines[0]);

    int problem_starts[MAX_PROBLEMS] = {0};
    int problem_count = 0;
    for(int i = 0; i < len; i++){
        if(lines[lines_count][i] == '+' || lines[lines_count][i] == '*'){
            problem_starts[problem_count++] = i;
        }
    }
    problem_t problems[MAX_PROBLEMS] = {0};
    for(int i = 0; i < problem_count; i++){
        int start = problem_starts[i];
        int end = (i + 1 < problem_count) ? problem_starts[i + 1] : len;

        int problem_len = end - start;
        char buff[problem_len+1];
        for(int j = 0; j < lines_count; j++){
            memcpy(buff, &lines[j][start], problem_len);
            buff[problem_len] = '\0';
            problems[i].nums[j] = atoi(buff);
        }
        problems[i].op = lines[lines_count][problem_starts[i]];
    }

    for(int i = 0; i < problem_count; i++){
        uint64_t problem_result = problems[i].nums[0];
        for(int j = 1; j < lines_count; j++){
            switch(problems[i].op){
                case '+':
                    problem_result += problems[i].nums[j];
                    break;
                case '*':
                    problem_result *= problems[i].nums[j];
                    break;
                default:
                    printf("Not a valid operator\n");
                    break;
            }
        }
        result += (uint64_t)problem_result;
    }


    printf("El resultado final es %" PRIu64 "\n", result);
    return 0;
}
