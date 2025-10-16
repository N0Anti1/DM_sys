#include "board.h"


board_t create_board() {
  board_t  b;
  int initial_board[6][9] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 1, 0, 0}, 
    {0, 0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 1, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0}
  };

  for(int i = 0; i < HEIGHT; i++){
    for(int j = 0; j < WIDTH; j++){
      b.board[i][j] = create_cell();
      b.board[i][j].is_trap = initial_board[i][j];
    }
  }
  for(int i = 0; i < NB_PLAYER_MAX; i++){
    b.hh_end[i] = 0;
  }
  return(b);
}

void init_board(board_t* b, int nb_player) {

  // Ajoute les joueurs
  for (int i = 0; i < NB_HEDGEHOG; i++) {
    for (int n = nb_player-1; n >= 0; n -= 1) {
      board_push(b, rand() % HEIGHT, 0, (char)(n+65));
    }
  }
}


void board_push(board_t* b, int line, int row, char ctn) {
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  cell_push(&(b->board[line][row]), ctn);
}

char board_pop(board_t* b, int line, int row){
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return cell_pop(&(b->board[line][row]));
}

int board_height(board_t* b, int line, int row){
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return cell_height(&(b->board[line][row]));
}

char board_top(board_t* b, int line, int row) {
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return cell_top(&(b->board[line][row]));
}

char board_peek(board_t* b, int line, int row, int pos){ // pos=0 => top
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return cell_peek(&(b->board[line][row]), pos);
}


bool board_is_trap(board_t* b, int line, int row){
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return(cell_is_trap(&(b->board[line][row])));
}


void board_print(board_t* b, int highlighted_line) {
  printf("option : 'o'\t\ttuto : 't'\n");
  for (int line = -1; line <= HEIGHT; line += 1) {
    for (int slice = 0; slice < 4; slice += 1) {
      for (int row = -1; row < WIDTH; row += 1) {


        if (line == -1) {
          if (row == -1) printf("     ");
          else if (slice == 0 && row == 0) printf(" START ");
          else if (slice == 0 && row == WIDTH-1) printf("FINISH ");
          else if (slice == 0 || slice == 1) printf("       ");
          else if (slice == 2) printf("  row  ");
          else if (slice == 3) printf("   %c   ", (char)(row+97));
        }

        else if (line < HEIGHT) {
          if (row == -1 && slice == 1) printf("line%c", highlighted_line == line ? '>' : ' ');
          else if (row == -1 && slice == 2) printf("  %d %c", line+1, highlighted_line == line ? '>' : ' ');
          else if (row == -1) printf("    %c", highlighted_line == line ? '>' : ' ');
          else {
            printf(" ");
            cell_print(&(b->board[line][row]), slice, highlighted_line == line);
            printf(" ");
          }
        }

        else if (line == HEIGHT) {
          if (row == -1) printf("     ");
          else if (slice == 0) printf("       ");
          else if (slice == 1) printf("  row  ");
          else if (slice == 2) printf("   %c   ", (char)(row+97));
        }

      }
      printf("\n");
    }
  }
}

