#include "day8.h"

// Union-Find variables
long uf_parent[MAX_BOXES_COUNT];
long uf_p_size[MAX_BOXES_COUNT] = {1};

junction_box_list_t list = {0};

int main(){
    FILE* input = fopen("input.txt", "r");
    char line[MAX_COORDENATE_LEN] = {0};
    while(fgets(line, MAX_COORDENATE_LEN, input) != NULL){
        sscanf(line, "%ld,%ld,%ld", &list.list[list.count].x, &list.list[list.count].y, &list.list[list.count].z);
        list.count++;
    }
    int conn_size = 10;
    int conn_pos = 0;
    connection_t *connections = calloc(conn_size, sizeof(connection_t));
    for(int i = 0; i < list.count; i++){
        for(int j = i + 1; j < list.count; j++){
            if(conn_pos >= conn_size){
                conn_size *= 2;
                connection_t* tmp = realloc(connections, conn_size * sizeof(connection_t));
                if(tmp) connections = tmp;
                else printf("Realloc failed\n");
            }
            connections[conn_pos].a = i;
            connections[conn_pos].b = j;
            connections[conn_pos].dist = calculate_distance(list.list[i], list.list[j]);
            conn_pos++;
        }
    }

    qsort(connections, conn_pos, sizeof(connection_t), sort_distances);

    for(int i = 0; i < list.count; i++) {
        uf_parent[i] = i;
        uf_p_size[i] = 1;
    }

    long result = 0;
    for(int i = 0; i < conn_pos; i++){
        int a = find(connections[i].a);
        int b = find(connections[i].b);
        if(a == b) continue;
        else {
            combine(a, b);
            result = list.list[connections[i].a].x * list.list[connections[i].b].x;
        }   
    }

    printf("El resultado final es %lu\n", result);

    free(connections);
    fclose(input);
    return 0;
}

int combine(long a, long b){
    if(uf_p_size[a] < uf_p_size[b]) {
       uf_p_size[b] += uf_p_size[a];
       uf_p_size[a] = 0;
       uf_parent[a] = b;
    } else {
        uf_p_size[a] += uf_p_size[b];
       uf_p_size[b] = 0;
        uf_parent[b] = a;
    }
    return 0;
}

long find(long x){
    long current = x;
    while(uf_parent[current] != current){
        current = uf_parent[current];
    }
    return current;
}

double calculate_distance(junction_box_t a, junction_box_t b){
    double x = 0, y = 0, z = 0;
    x = pow(a.x - b.x, 2);
    y = pow(a.y - b.y, 2);
    z = pow(a.z - b.z, 2);
    return sqrt(x + y + z);
}

int sort_distances(const void *p1, const void *p2){
    const connection_t *p1_conn = (const connection_t*)p1;
    const connection_t *p2_conn = (const connection_t*)p2;
    if(p1_conn->dist > p2_conn->dist) return 1;
    if(p1_conn->dist < p2_conn->dist) return -1;
    return 0;
}