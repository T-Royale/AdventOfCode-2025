#include "day10.h"

int main(){
    uint64_t result = 0;
    FILE *input = fopen("input.txt", "r");
    char buff[MAX_LINE_LEN];
    while(fgets(buff, MAX_LINE_LEN, input) != NULL){
        diagram_t target = 0;
        buttons_t buttons = {0};
        bool parsingTarget = false;
        bool parsingButton = false;
        uint64_t lights_count = 0;
        for(int i = 0; i < strlen(buff); i++){
            char c = buff[i];
            switch(c){
                case '[':
                    parsingTarget = true;
                    target = 0;
                    lights_count = 0;
                    break;
                case ']':
                    parsingTarget = false;
                    break;
                case '(':
                    parsingButton = true;
                    buttons.value[buttons.count] = 0;
                    break;
                case ')':
                    parsingButton = false;
                    buttons.count++;
                    if(buttons.count >= MAX_BUTTONS){
                        printf("ERROR: Buttons bigger than max value\n");
                        return -1;
                    }
                    break;
                default:
                    if (parsingTarget) {
                        if (c == '#') target |= (1u << lights_count);
                        lights_count++;
                    } 
                    else if (parsingButton && c >= '0' && c <= '9') {
                        int n = c - '0';
                        buttons.value[buttons.count] |= (1u << n);
                    }
                    break;
            }
        }
        result += min_steps(target, &buttons, lights_count);
    }
    printf("El resultado es: %" PRIu64 "\n", result);
    return 0;
}

int min_steps(diagram_t target, buttons_t *buttons, uint64_t lights_count){
    int states = 1 << lights_count;
    bool prev[states];
    bool current[states];
    bool visited[states];
    for(int i = 0; i < states; i++){
        current[i] = false;
        prev[i] = false;
        visited[i] = false;
    }
    if(target == INITIAL_STATE) return 0;
    visited[INITIAL_STATE] = true;
    for(int i = 0; i < buttons->count; i++) {
        if(buttons->value[i] == target){
            return 1;
        }
        prev[buttons->value[i]] = true;
        visited[buttons->value[i]] = true;
    }
    int steps = 1;
    while(steps < MAX_STEPS){
        steps++;
        for(int i = 0; i < states; i++){
            if(prev[i]){
                for(int j = 0; j < buttons->count; j++){
                    diagram_t new = i ^ buttons->value[j];
                    if(visited[new]) continue;
                    if(new == target) return steps;
                    else{
                        current[new] = true;
                        visited[new] = true;
                    }
                }
            }
        }
        memcpy(prev, current, sizeof(prev));
        for(int i = 0; i < states; i++) current[i] = false;
    }
    return steps;
}