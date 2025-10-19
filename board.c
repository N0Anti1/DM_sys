#include "board.h"


// Create a board with a given proportion of trap and wall
board_t create_board(int width, int height, int nb_hedgehog, float trap, float wall) {
  board_t  b;
  b.width = width;
  b.height = height;
  b.nb_hedgehog = nb_hedgehog;

  // Initialises the board's tiles
  float random;
  
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      b.board[i][j] = create_cell();
      random = rand() / (float)RAND_MAX;
      if (random < trap) {
        if (j > 0 && j < width - 1) {
          b.board[i][j].type = TRAP;
        }
      }
      else if (random < trap + wall) {
        if (j > 0) b.board[i][j].type = WALL;
      }
    }
  }
  // Checks whether whole a row is a continuous wall
  // Leaves a spaces if that's the case
  bool check = true;
  int hole;
  for (int j = 0; j < width; j++) {
    check = true;
    for (int i = 0; i < height; i++) {
      if (check) {
        check = b.board[i][j].type == WALL;
      }
    }
    if (check) {
      hole = rand() % height;
      b.board[hole][j].type = BLANK;
    }
  }

  // Initialises the players' scores
  for (int i = 0; i < NB_PLAYER_MAX; i++) {
    b.hh_end[i] = 0;
  }
  return (b);
}

// Add hedgehogs to the start position randomly
void init_board(board_t* b, int nb_player) {
  int hh_count[NB_PLAYER_MAX]; // Count how many hedgehogs are left to place
  for (int i = 0 ; i < nb_player ; i++) {
    hh_count[i] = b->nb_hedgehog;
  }

  int next_hh_placed;
  int next_line;
  for (int i = 0 ; i < (nb_player * b->nb_hedgehog) ; i++) {
    next_hh_placed = rand() % nb_player;
    next_line = rand() % b->height;
    // If the player has already placed all his hedgehogs :
    while (hh_count[next_hh_placed] == 0) {
      next_hh_placed++;
      if (next_hh_placed == nb_player) {
          next_hh_placed = 0;
        }
    }
    hh_count[next_hh_placed]--;
    board_push(b, next_line, 0, (char)(next_hh_placed + 65));
  }
}

int get_width(board_t* b) {
  return b->width;
}
int get_height(board_t* b) {
  return b->height;
}
int get_nb_hedgehog(board_t* b) {
  return b->nb_hedgehog;
}



void board_push(board_t* b, int line, int row, char ctn) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  cell_push(&(b->board[line][row]), ctn);
}

char board_pop(board_t* b, int line, int row) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return cell_pop(&(b->board[line][row]));
}

int board_height(board_t* b, int line, int row) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return cell_height(&(b->board[line][row]));
}

char board_top(board_t* b, int line, int row) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return cell_top(&(b->board[line][row]));
}

char board_peek(board_t* b, int line, int row, int pos) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return cell_peek(&(b->board[line][row]), pos);
}


bool board_is_trap(board_t* b, int line, int row) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return (cell_is_trap(&(b->board[line][row])));
}

bool board_has_wall(board_t* b, int line, int row) {
  assert(0 <= row && row < b->width && 0 <= line && line < b->height);
  return (cell_has_wall(&(b->board[line][row])));
}


void board_print(board_t* b, int highlighted_line) {
  printf("option : 'o'\t\ttuto : 't'\n");
  for (int line = -1; line <= b->height; line += 1) {
    for (int slice = 0; slice < 4; slice += 1) {
      for (int row = -1; row < b->width; row += 1) {

        if (line == -1) {
          if (row == -1) printf("     ");
          else if (slice == 0 && row == 0) printf(" START ");
          else if (slice == 0 && row == b->width-1) printf("FINISH ");
          else if (slice == 0 || slice == 1) printf("       ");
          else if (slice == 2) printf("  row  ");
          else if (slice == 3) printf("   %c   ", (char)(row+97));
        }

        else if (line < b->height) {
          if (row == -1 && slice == 1) printf("line%c", highlighted_line == line ? '>' : ' ');
          else if (row == -1 && slice == 2) printf("  %d %c", line+1, highlighted_line == line ? '>' : ' ');
          else if (row == -1) printf("    %c", highlighted_line == line ? '>' : ' ');
          else {
            printf("%s", board_has_wall(b, line, row) ? "▒" : " ");
            cell_print(&(b->board[line][row]), slice, highlighted_line == line);
            printf(" ");
          }
        }

        else if (line == b->height) {
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

