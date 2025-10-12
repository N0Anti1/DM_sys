#include "board.h"


board_t create_board() {
  board_t  b;
  for(int i = 0; i < HEIGHT; i++){
    for(int j = 0; j < WIDTH; j++){
      b.board[i][j] = create_cell();
    }
  }
  for(int i = 0; i < NB_PLAYER_MAX; i++){
    b.hh_end[i] = 0;
  }
  return(b);
}

// Il faut vérifier que la case existe bien !!
void board_push(board_t* b, int line, int row, char ctn) {
  cell_push(&(b->board[line][row]), ctn);
}

// Il faut vérifier que la case existe bien !!
char board_pop(board_t* b, int line, int row){
  cell_pop(&(b->board[line][row]));
}

// Il faut vérifier que la case existe bien !!
int board_height(board_t* b, int line, int row){
  cell_height(&(b->board[line][row]));
}

// Il faut vérifier que la case existe bien !!
char board_top(board_t* b, int line, int row) {
  cell_top(&(b->board[line][row]));
}

// Il faut vérifier que la case existe bien !!
char board_peek(board_t* b, int line, int row, int pos){ // pos=0 => top
  cell_peek(&(b->board[line][row]), pos);
}

// Il faut vérifier que la case existe bien !!
// Puis c'est vrai que cette fonction est inutile...
// De plus tu peux simplement renvoyer :
// return board_height(b, line, row) == 0;
// Mais du coup plutôt que d'utiliser cette fonction on peut tester la condition ci-dessus...
bool board_is_empty(board_t* b, int line, int row){
  if(board_height(b, line, row) == 0){
    return(true);
  } else {
    return(false);
  }
}

// Il faut vérifier que la case existe bien !!
bool board_is_trap(board_t* b, int line, int row){
  return(cell_is_trap(&(b->board[line][row])));
}


void board_print(board_t* b, int highlighted_line) {
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


// ELISA :
void init_board(board_t* b, int nb_player) {
  // Place les pièges
  b->board[0][2].is_trap = true;

  // Ajoute les joueurs
  for (int i = 0; i < NB_HEDGEHOG; i++) {
    for (int n = nb_player-1; n >= 0; n -= 1) {
      board_push(b, rand() % HEIGHT, 0, (char)(n+65));
    }
  }
}
