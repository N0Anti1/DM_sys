#include "board.h"


int nb_line = 6;
int nb_row= 9;

board_t create_board(){
  board_t  b;
  for(int i=0; i<nb_line; i++){
    for(int j=0; j<nb_row; j++){
      b.board[i][j]=cell_create();
    }
  }
  for(int i=0; i<26; i++){
    b.hh_end[i]=0;
  }
  return(b);
}

void board_push(board_t* b, int line, int row, char ctn){
  heap_push(b->board[line][row], ctn);
}

char board_pop(board_t* b, int line, int row){
  heap_pop(b->board[line][row]);
}

int board_height(board_t* b, int line, int row){
  heap_height(b->board[line][row]);
}

char board_top(board_t* b, int line, int row) {
  heap_top(b->board[line][row]);
}

char board_peek(board_t* b, int line, int row, int pos){ // pos=0 => top
  heap_peek(b->board[line][row], pos);
}

void board_print(board_t* b, int highlighted_line);

bool board_is_empty(board_t* b, int line, int row){
  if(board_height(b, line, row)==0){
    return(true);
  } else {
    return(false);
  }
}

bool board_is_trap(board_t* b, int line, int row){
  return(b[line][row].is_trap);
}