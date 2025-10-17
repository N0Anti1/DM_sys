#include "board.h"


board_t create_board(float trap, float wall) {
  board_t  b;
<<<<<<< HEAD
  int initial_board[6][9] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 1, 0, 0}, 
    {0, 0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 1, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0}
  };

=======
  //Initialises the board's tiles
  float random;
>>>>>>> 20b70b9 (ajout des murs)
  for(int i = 0; i < HEIGHT; i++){
    for(int j = 0; j < WIDTH; j++){
      b.board[i][j] = create_cell();
      random = rand() / (float)RAND_MAX;
      if(random < trap && j > 0 && j < WIDTH - 1) {
        b.board[i][j].type = TRAP;
      }
      else if(random < trap + wall && j > 0) {
        b.board[i][j].type = WALL;
      }
    }
  }
  //Checks whether whole a row is a continuous wall and leaves a spaces if that's the case
  bool check = true;
  int hole;
  for(int j = 0; j < WIDTH; j++){
    check = true;
    for(int i = 0; i < HEIGHT; i++){
      if(check){
        check = b.board[i][j].type == WALL;
      }
    }
    if(check) {
      hole = rand() % HEIGHT;
      b.board[hole][j].type = BLANK;
    }
  }

  //Initialises the players' scores
  for(int i = 0; i < NB_PLAYER_MAX; i++){
    b.hh_end[i] = 0;
  }
  return(b);
}

//Ajoute les hérisson à leur position de départ de manière aléatoire
void init_board(board_t* b, int nb_player) {
 int hh_count[NB_PLAYER_MAX]; //tableau donnant le nombre de hérisson restant à placer par joueur
 for(int i = 0 ; i < nb_player ; i++){ //initialisation de ce tableau
   hh_count[i] = NB_HEDGEHOG;
 }
 int next_hh_placed;
 int next_line;
 for(int i = 0 ; i < (nb_player * NB_HEDGEHOG) ; i++){
   next_hh_placed = rand() % nb_player; //le prochain hérisson à être placé appartient au joueur nhp
   next_line = rand() % HEIGHT; //le prochain hérisson sera placé sur la ligne nl
   while(hh_count[next_hh_placed] == 0) { //gère le cas où le joueur à ajouter a déjà tous ses hérissons de placés
    next_hh_placed++; 
    if(next_hh_placed == nb_player) {
       next_hh_placed = 0;
     }
   }
   hh_count[next_hh_placed]--; //décrémente le nombre de hérisson à placer pour le joueur nhp
   board_push(b, next_line, 0, (char) next_hh_placed+65); //place le hérisson du joueur nhp sur la ligne nl de la première colonne
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
bool board_has_wall(board_t* b, int line, int row){
  assert(0 <= row && row < WIDTH && 0 <= line && line < HEIGHT);
  return(cell_has_wall(&(b->board[line][row])));
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
            printf("%s", board_has_wall(b, line, row) ? "▒" : " ");
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


