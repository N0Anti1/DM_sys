#include "data.h"


#ifndef CELL_H
#define CELL_H


typedef struct cell {
    char heap[NB_HEDGEHOG*NB_PLAYER_MAX];
    int size;
    bool is_trap;
} cell_t;


cell_t create_cell();

void cell_push(cell_t* c, char ctn);
char cell_pop(cell_t* c);
int cell_height(cell_t* c);
char cell_top(cell_t* c);
char cell_peek(cell_t* c, int pos); // pos=0 => top

bool cell_is_trap(cell_t* c);

void cell_print(cell_t* c, int slice, bool highlighted);


#endif
