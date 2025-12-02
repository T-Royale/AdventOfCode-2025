#include "main.h"

int main(){
    char input_path[] = "input.txt";
    FILE* input_fd = fopen(input_path, "r");
    if(!input_fd) {
        perror("fopen");
        return 1;
    }
    uint64_t start;
    uint64_t end;
    uint64_t result = 0;
    int i = 0;
    while(fscanf(input_fd, "%" SCNu64 "-%" SCNu64, &start, &end) == 2){
        for(uint64_t i = start; i <= end; i++){
            if(is_invalid_id(i)) result += i;
        }
        // Reads ',' or EOF
        int c = fgetc(input_fd);
        if (c == EOF) break;
        i++;
    }
    fclose(input_fd);
    printf("Resultado: %" PRIu64 "\n", result);
    return 0;
}

bool is_invalid_id(uint64_t id){
    char str[MAX_DIGITS+1];
    sprintf(str, "%" PRIu64, id);
    int len = strlen(str);
    if(len % 2 != 0) return false;

    for(int i = 0; i < len/2; i++){
        if(str[i] != str[len/2 + i]) return false;
    }
    
    return true;
}