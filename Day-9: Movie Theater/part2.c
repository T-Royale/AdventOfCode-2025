#include "day9.h"

int main() {
    int64_t result = 0;
    FILE* input = fopen("input.txt", "r");
    point_t squares[MAX_SQUARE_COUNT];
    int count = 0;
    char buff[MAX_LINE_LEN];
    while(fgets(buff, MAX_LINE_LEN, input) != NULL){
        sscanf(buff, "%d,%d\n", &squares[count].x, &squares[count].y);
        count++;
    }
    // Define the sides of the polygon
    segment_t edges[count];
    for(int i = 0; i < count; i++){
        int j = (i + 1) % count;
        edges[i] = (segment_t){squares[i].x, squares[i].y, squares[j].x, squares[j].y};
    }
    // Find valid Y positions
    int y_min = squares[0].y;
    int y_max = squares[0].y;
    for(int i = 0; i < count; i++){
        if(squares[i].y < y_min) y_min = squares[i].y;
        if(squares[i].y > y_max) y_max = squares[i].y;
    }
    int row_count = y_max - y_min + 1;
    row_t rows[row_count];

    for(int y = y_min; y <= y_max; y++){    // Recorrer Y validas
        rows[y-y_min].row = y;              // Guardar posición Y
        int cruces[count];
        int pos = 0;
        // Anota las lineas verticales que cortan una linea Y
        for(int i = 0; i < count; i++){
            if(edges[i].x1 != edges[i].x2) continue;
            int y0 = MIN(edges[i].y1, edges[i].y2);
            int y1 = MAX(edges[i].y1, edges[i].y2);
            if (y >= y0 && y < y1) {
                cruces[pos++] = edges[i].x1;
            }
        }
        qsort(cruces, pos, sizeof(int), sort_elements);
        rows[y-y_min].count = pos/2;    // pos tiene todos los cruces, cada dos cruces es un intervalo válido
        rows[y-y_min].intervals = calloc(rows[y-y_min].count, sizeof(interval_t));
        // Anota los intervalos validos
        for(int i = 0; i < pos/2; i++){
            rows[y-y_min].intervals[i].l = cruces[i*2];
            rows[y-y_min].intervals[i].r = cruces[i*2+1];
        }
    }

    for(int i = 0; i < count; i++){
        for(int j = i+1; j < count; j++){
            int xL = MIN(squares[i].x, squares[j].x);
            int xR = MAX(squares[i].x, squares[j].x);
            int yB = MIN(squares[i].y, squares[j].y);
            int yT = MAX(squares[i].y, squares[j].y);

            if (xL == xR || yB == yT) continue;

            if (rectangle_is_valid(xL, xR, yB, yT, rows, y_min)) {
                int64_t dx =  llabs(squares[i].x - squares[j].x) + 1;
                int64_t dy =  llabs(squares[i].y - squares[j].y) + 1;
                int64_t area = dx * dy;
                if(area > result) {
                    result = area;
                }
            }
        }
    }

    printf("The result is %" PRId64 "\n", result);
    return 0;
}

bool rectangle_is_valid(int xL, int xR, int yB, int yT, row_t* rows, int y_min){
    for(int y = yB; y < yT; y++){
        bool isvalid = false;
        row_t *row = &rows[y - y_min];
        for(int i = 0; i < row->count; i++){
            int l = row->intervals[i].l;
            int r = row->intervals[i].r;
            if(l <= xL && r >= xR) {
                isvalid = true;
                break;
            }
        }
        if(!isvalid) return false;
    }
    return true;
}

int sort_elements(const void* p1, const void* p2){
    int* v1 = (int*)p1;
    int* v2 = (int*)p2;
    if(*v1 > *v2) return 1;
    else return -1;
}