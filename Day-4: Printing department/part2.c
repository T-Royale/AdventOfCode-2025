#include "day4.h"

int main(){
    int result = 0;
    FILE* input = fopen("input.txt", "r");
    char grid[MAX_LINE_COUNT][MAX_LINE_LEN];
    int row_count = 0;
    // Fill grid
    while (row_count < MAX_LINE_COUNT && fgets(grid[row_count], MAX_LINE_LEN, input)) {
        grid[row_count][strcspn(grid[row_count], "\n")] = '\0';
        row_count++;
    }
    int len = strlen(grid[0]);
    int paper_rolls_removed = 0;
    do {
        // Get available paper rolls
        for(int i = 0; i < row_count; i++){
            for(int j = 0; j < len; j++){
                if(grid[i][j] == '@'){
                    if(is_valid_paper_roll(grid, j, i, len, row_count)){
                        grid[i][j] = 'x';   //Mark as going to be removed
                        result++;
                    }
                }
            }
        }
        // Remove paper rolls
        paper_rolls_removed = 0;
        for(int i = 0; i < row_count; i++){
            for(int j = 0; j < len; j++){
                if(grid[i][j] == 'x'){
                    grid[i][j] = '.';
                    paper_rolls_removed++;
                }   
            }
        }
        printf("Removed %d paper rolls\n", paper_rolls_removed);
    } while (paper_rolls_removed > 0);
    printf("The result is: %d\n", result);
    fclose(input);
    return 0;
}

bool is_valid_paper_roll(char grid[MAX_LINE_COUNT][MAX_LINE_LEN], int pos_x, int pos_y, int max_x, int max_y){
    int roll_count = 0;
    //Upper-left
    if(pos_x-1 >= 0 && pos_y-1 >= 0) increment_count_if_valid(pos_y-1, pos_x-1);
    // Upper
    if(pos_y-1 >= 0) increment_count_if_valid(pos_y-1, pos_x);
    // Upper-right
    if(pos_y-1 >= 0 && pos_x+1 < max_x) increment_count_if_valid(pos_y-1, pos_x+1);
    // Right
    if(pos_x+1 < max_x) increment_count_if_valid(pos_y, pos_x+1);
    // Lower-right
    if(pos_y+1 < max_y && pos_x+1 <= max_x) increment_count_if_valid(pos_y+1, pos_x+1);
    // Down
    if(pos_y+1 < max_y) increment_count_if_valid(pos_y+1, pos_x);
    // Lower-Left
    if(pos_y+1 < max_y && pos_x-1 >= 0) increment_count_if_valid(pos_y+1, pos_x-1);
    // Left
    if(pos_x-1 >= 0) increment_count_if_valid(pos_y, pos_x-1);
    return (roll_count < 4);
}