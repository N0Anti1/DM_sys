#include "cell.h"


#ifndef BOARD_H
#define BOARD_H

typedef struct board {
    cell_t board[HEIGHT][WIDTH];
    int hh_end[NB_PLAYER_MAX];     // Amount of hedgehog at the end of the race
} board_t;


board_t create_board(float trap, float wall);
void init_board(board_t* b, int nb_player);

void board_push(board_t* b, int line, int row, char ctn);
char board_pop(board_t* b, int line, int row);
int board_height(board_t* b, int line, int row);
char board_top(board_t* b, int line, int row);
char board_peek(board_t* b, int line, int row, int pos); // pos=0 => top

bool board_is_trap(board_t* b, int line, int row);
bool board_has_wall(board_t* b, int line, int row);

void board_print(board_t* b, int highlighted_line);


#endif
