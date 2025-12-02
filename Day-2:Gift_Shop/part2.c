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
    printf("Result: %" PRIu64 "\n", result);
    return 0;
}

bool is_invalid_id(uint64_t id){
    char str[MAX_DIGITS+1];
    sprintf(str, "%" PRIu64, id);
    int len = strlen(str);
    
    for(int block_len = 1; block_len < len; block_len++){
        bool v = true;
        if(len % block_len == 0){
            for(int i = block_len; i < len; i++){
                if(str[i] != str[i % block_len]){
                    v = false;
                    break;
                }
            }
            if(v) return true;
        }
    }
    
    return false;
}