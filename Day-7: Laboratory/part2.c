#include "day7.h"

int main(void){
    uint64_t result;
    FILE* input = fopen("input.txt", "r");
    char line[MAX_LINE_LEN] = {0};
    fgets(line, MAX_LINE_LEN, input);
    int len = strlen(line);
    uint64_t tachyons[len];
    for(int i = 0; i < len; i++){
        if(line[i] == 'S') tachyons[i] = 1;
        else tachyons[i] = 0;
    }
    while(fgets(line, MAX_LINE_LEN, input) != NULL){
        for(int i = 0; i < len; i++){
            if(line[i] == '^' && tachyons[i] > 0){
                if(i > 0) tachyons[i-1] += tachyons[i];
                if(i < len-1) tachyons[i+1] += tachyons[i];
                tachyons[i] = 0;
            }
        }
    }
    for(int i = 0; i < len; i++){
        result += tachyons[i];
    }
    printf("El resultado final es %" PRIu64 "\n", result);
    fclose(input);
    return 0;
}
