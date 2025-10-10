#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cell.h"


#ifndef BOARD_H
#define BOARD_H

typedef struct board {
    cell_t** board;
    int hh_end[26];     // Amount of hedgehog at the end of the race
} board_t;


board_t create_board();
void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos); // pos=0 => top
void board_print(board_t* b, int highlighted_line);
bool board_is_empty(board_t* b, int line, int row);
bool board_is_trap(board_t* b, int line, int row);



#endif
