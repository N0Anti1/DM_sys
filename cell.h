#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#ifndef CELL_H
#define CELL_H

typedef struct cell {
    char* heap;
    int size;
    bool is_trap;
} cell_t;


cell_t create_cell();
void cell_push(cell_t* b, char ctn);
char cell_pop(cell_t* b);
int cell_height(cell_t* b);
char cell_top(cell_t* b);
char cell_peek(cell_t* b, int pos); // pos=0 => top
void cell_print(cell_t* b, int slice);
bool cell_is_trap(cell_t* c);


#endif
