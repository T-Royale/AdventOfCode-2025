#include "day9.h"

int main() {
    int64_t result = 0;
    FILE* input = fopen("input.txt", "r");
    red_squares_t squares[MAX_SQUARE_COUNT];
    int count = 0;
    char buff[MAX_LINE_LEN];
    while(fgets(buff, MAX_LINE_LEN, input) != NULL){
        sscanf(buff, "%d,%d\n", &squares[count].x, &squares[count].y);
        count++;
    }
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            if(i == j) continue;
            int64_t dx =  llabs(squares[i].x - squares[j].x) + 1;
            int64_t dy =  llabs(squares[i].y - squares[j].y) + 1;
            int64_t area = dx * dy;
            if(area > result) {
                result = area;
            }
        }
    }
    printf("The result is %" PRId64 "\n", result);
    return 0;
}
