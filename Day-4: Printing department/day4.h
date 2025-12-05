#include "../clibs.h"

const int MAX_LINE_LEN = 256;
const int MAX_LINE_COUNT = 256;

#define increment_count_if_valid(y,x) if(grid[y][x] == '@' || grid[y][x] == 'x') roll_count++;

bool is_valid_paper_roll(char grid[MAX_LINE_COUNT][MAX_LINE_LEN], int pos_x, int pos_y, int max_x, int max_y);