#include "day7.h"

int main(void){
    int result;
    FILE* input = fopen("input.txt", "r");
    char line[MAX_LINE_LEN] = {0};
    fgets(line, MAX_LINE_LEN, input);
    int len = strlen(line);
    bool tachyons[len];
    for(int i = 0; i < len; i++){
        if(line[i] == 'S') tachyons[i] = true;
        else tachyons[i] = false;
    }
    while(fgets(line, MAX_LINE_LEN, input) != NULL){
        for(int i = 0; i < len; i++){
            if(line[i] == '^' && tachyons[i]){
                tachyons[i] = false;
                if(i > 0) tachyons[i-1] = true;
                if(i < len-1) tachyons[i+1] = true;
                result++;
            }
        }
    }
    printf("El resultado final es %d\n", result);
    fclose(input);
    return 0;
}
