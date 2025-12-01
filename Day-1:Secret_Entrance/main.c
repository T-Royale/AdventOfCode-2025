#include "main.h"

int main(int argc, char** argv){
    int dial = 50;    // Exercise says the dial starts at 50
    int result = 0;
    char c;
    char* path = "input.txt";
    while((c = getopt(argc, argv, "f:h")) != -1){
        switch(c){
            case 'f':
                path = optarg;
                break;
            case 'h':
                printf("flag -f to specify a path to an input file\n\
                        takes input.txt as default input file\n\
                        program will output the password\n");
                exit(0);
                break;
            default:
                break;
        }
    }
    if(!parse_file(path, &dial, &result)) {
        printf("error on parse_file\n");
        exit(0);
    }
    printf("Result: %d\n", result);
    return 0;
}

bool parse_file(char *path, int *dial, int *result){
    FILE* input = fopen(path, "r");
    if(!input) return false;

    char line[LINE_LEN];
    while(fgets(line, LINE_LEN, input)){
        char direction;
        int number;
        int n = sscanf(line, "%c%d", &direction, &number);
        if(n != 2){
            printf("sscanf failed\n");
            return false;
        }        
        int full = number/100;
        int zeros = full;
        number %= 100;
        if(direction == 'R'){
            if(*dial + number >= 100) zeros++;
            *dial = (*dial + number) % 100;
        } else if (direction == 'L'){
            if(*dial > 0 && number >= *dial) zeros++;
            *dial = (*dial - number + 100) % 100;
        } else {
            printf("Invalid Operation:%c\n", direction);
            return false;
        }
        *result += zeros;
    }
    fclose(input);
    return true;
}