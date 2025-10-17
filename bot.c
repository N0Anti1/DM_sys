#include "bot.h"


bot_t init_bot (int player){
    bot_t ia;
    ia.player = player;
    ia.nb_moves = 0;
    return ia;
}

void playable_moves_vu(bot_t* ia, board_t* b){
    for (int row = 0; row < WIDTH-1; row+=1){
        for (int line = 0; line < HEIGHT; line+=1){
            if (is_playable_v(b, line, row, ia->player, true)){
                ia->playable_moves[ia->nb_moves][0] = row;
                ia->playable_moves[ia->nb_moves][1] = line;
                ia->nb_moves += 1;
            }
        }
    }
}

void playable_moves_vd(bot_t* ia, board_t* b){
    for (int row = 0; row < WIDTH-1; row+=1){
        for (int line = 0; line < HEIGHT; line+=1){
            if (is_playable_v(b, line, row, ia->player, false)){
                ia->playable_moves[ia->nb_moves][0] = row;
                ia->playable_moves[ia->nb_moves][1] = line;
                ia->nb_moves += 1;
            }
        }
    }
}

void playable_moves_h(bot_t* ia, board_t* b, int line){
    for (int row = 0; row < WIDTH-1; row+=1){
        if (is_playable_h(b, line, row)){
            ia->playable_moves[ia->nb_moves][0] = row;
            ia->playable_moves[ia->nb_moves][1] = line;
            ia->nb_moves += 1;
        }
    }
}

bool play_bot_v(bot_t* ia, board_t* b, bool mov){
    if (mov) {playable_moves_vu(ia, b);}
    else {playable_moves_vd(ia, b);}
    if (ia->nb_moves != 0){
        int rd = rand() % ia->nb_moves;
        int coups[2]; coups[0] = ia->playable_moves[rd][0]; coups[1] = ia->playable_moves[rd][1];
        play_v(b, coups[1], coups[0], mov);
        // printf("Le bot a joué en vertical : %c%d\n", (char)(coups[0]+65), coups[1]+1);
        ia->played_move[0][0] = coups[0];
        ia->played_move[0][1] = coups[1];
        ia->nb_moves = 0;
        return true;
    }
    else {
        // printf("bot %c n'a pas joué v\n",ia->player);
        return false;
    }
}

void play_bot_h(bot_t* ia, board_t* b, int line){
    playable_moves_h(ia, b, line);
    if (ia->nb_moves != 0){
        int rd = rand() % ia->nb_moves;
        int coups[2]; coups[0] = ia->playable_moves[rd][0]; coups[1] = ia->playable_moves[rd][1];
        play_h(b, coups[1], coups[0]);
        // printf("Le bot a joué en horizontal : %c%d\n", (char)(coups[0]+65), coups[1]+1);
        ia->played_move[1][0] = coups[0];
        ia->played_move[1][1] = coups[1];
        ia->nb_moves = 0;
    }
    else {
        // printf("bot %c n'a pas joué h\n",ia->player);
    }
}

bool bot_turn(bot_t* ia, board_t* b, int line){
    int pv = rand() % 3; // pv=0 -> up, pv=1 -> down, pv=2 -> passe
    bool vertical_move = false;
    memset(&(ia->played_move), -1, sizeof(ia->played_move));
    if (pv == 0) {
        if (play_bot_v(ia, b, true)) vertical_move = true;
    }
    else if (pv == 1) play_bot_v(ia, b, false);

    play_bot_h(ia, b, line);

    return vertical_move;
}


void cell_print_bot(cell_t* c, int slice, bool mov, bool dir, bool start) {
    if (slice == 0) {
        if (cell_is_trap(c)) printf(" VVV ");
        else if (mov && dir && start) printf(" -|- ");
        else if (mov && !dir && !start) printf(" -V- ");
        else printf(" --- ");
    }
    else if (slice == 1) {
        if (cell_is_trap(c)) printf(">");
        else printf("|");
        if (cell_height(c) > 0) {
            printf("%c%c%c", cell_top(c), cell_top(c), cell_top(c));
        }
        else {
            printf("   ");
        }
        if (cell_is_trap(c)) printf("<");
        else printf("|");
    }
    else if (slice == 2) {
        if (cell_is_trap(c)) printf(">");
        else printf("|");

        if (cell_height(c) == 0) {
            printf("   ");
        }
        else if (cell_height(c) == 1) {
            printf("%c%c%c", cell_top(c), cell_top(c), cell_top(c));
        }
        else if (cell_height(c) == 2) {
            // +32 to have lowercase
            printf("%c%c%c", cell_peek(c, 1)+32, cell_peek(c, 1)+32, cell_peek(c, 1)+32);
        }
        else if (cell_height(c) == 3) {
            printf("%c %c", cell_peek(c, 1)+32, cell_peek(c, 2)+32);
        }
        else if (cell_height(c) >= 4) {
            printf("%c%c%c", cell_peek(c, 1)+32, cell_peek(c, 2)+32, cell_peek(c, 3)+32);
        }

        if (cell_is_trap(c)) printf("<");
        else printf("|");
    }    
    else if (slice == 3) {
        char c1 = '-', c2 = '-', c3 = '-';
        if (cell_is_trap(c)) {
            c1 = '^';
            c2 = '^';
            c3 = '^';
        }
        if (cell_height(c) >= 100) c1 = (char)(cell_height(c)/100+48);
        if (cell_height(c) >= 10) c3 = (char)(cell_height(c)%10+48);
        if (cell_height(c) >= 10) c2 = (char)((cell_height(c)%100)/10+48);
        else if (cell_height(c) > 1) c2 = (char)(cell_height(c)+48);
        if (mov && dir && !start) c2 = '^';
        else if (mov && !dir && start) c2 = '|';
        printf(" %c%c%c ", c1, c2, c3);
    }
}

void board_print_bot(board_t* b, bot_t* ia, bool dir) {
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
          if (row == -1 && slice == 1) printf("line ");
          else if (row == -1 && slice == 2) printf("  %d  ", line+1);
          else if (row == -1) printf("     ");
          else {
            if (slice == 1 && ia->played_move[1][0] == row-1 && ia->played_move[1][1] == line) {
                printf(">");
            }
            else printf(" ");
            if (ia->played_move[0][0] == row && ia->played_move[0][1] == line) {
                cell_print_bot(&(b->board[line][row]), slice, true, dir, ia->played_move[0][1] == line);
            }
            else if (ia->played_move[0][0] == row && ia->played_move[0][1] + !dir == line + dir) {
                cell_print_bot(&(b->board[line][row]), slice, true, dir, ia->played_move[0][1] == line);
            }
            else cell_print_bot(&(b->board[line][row]), slice, false, dir, false);
            if (slice == 1 && ia->played_move[1][0] == row && ia->played_move[1][1] == line) {
                printf("-");
            }
            else printf(" ");
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

  int nb_move = 0;
  if (ia->played_move[0][0] != -1) nb_move += 1;
  if (ia->played_move[1][0] != -1) nb_move += 1;
  printf("Le bot %c a joué %d coup%s!\n", (char)(ia->player+65), nb_move, nb_move > 1 ? "s " : " ");
}

