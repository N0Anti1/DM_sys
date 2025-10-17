#include "logic.h"



bool verif_trap(board_t* b, int line, int row){
    if (board_is_trap(b, line, row) && board_height(b, line, row) == 1) {
        for (int i = 0; i < row; i+=1){
            if (board_height(b, line, i) != 0) {return false;}
        }
    }
    return true;
}

bool is_playable_h(board_t* b, int line, int row){
    if (line < 0 || line >= HEIGHT || row < 0 || row >= WIDTH-1) {return false;}
    return (verif_trap(b, line, row) && (board_height(b, line, row) != 0));
}

bool is_playable_v(board_t* b, int line, int row, int player, bool mov){
    if (line < 0 || line >= HEIGHT || row < 0 || row >= WIDTH-1) {return false;}
    if ((mov && line == 0) || (!mov && line == HEIGHT-1)) {return false;}
    if (board_height(b,line,row) == 0) {return false;}
    return (verif_trap(b,line,row) && board_top(b, line, row)==player+65);
}

void play_h(board_t* b, int line, int row){
    assert(line >= 0 && line < HEIGHT && row >= 0 && row < WIDTH-1);
    char player = board_pop(b,line,row);
    board_push(b,line,row+1,player);
    if (row == WIDTH-2) {b->hh_end[((int)player)-65]+=1;}
}

void play_v(board_t* b, int line, int row, bool mov){
    assert(mov <= line && line < HEIGHT - !mov && 0 <= row && row < WIDTH);
    if (mov) {board_push(b,line-1,row,board_pop(b,line,row));}
    else {board_push(b,line+1,row,board_pop(b,line,row));}
}


bool is_line_empty(board_t* b, int line){
    assert(0 <= line && line < HEIGHT);
    for (int i = 0; i < WIDTH-1; i+=1){
        if (board_height(b, line, i) > 0) {return false;}
    }
    return true;
}

bool is_game_end(board_t* b) {
    for (int i = 0; i < NB_PLAYER_MAX; i+=1){
        if (b->hh_end[i] == NB_HEDGEHOG-1){
            return true;
        }
    }
    return false;
}


void print_classement(board_t* b, int nb_player){
    int rank = 1;
    bool print = true;
    for (int n = NB_HEDGEHOG-1; n >= 0 && rank <= nb_player; n-=1){
        if (print){
            printf("- Place #%d :",rank);
            print = false;
        }
        for (int i = 0; i < nb_player; i+=1){
            if (b->hh_end[i]==n){
                printf("%s équipe %c", print ? "," : "", (i+65));
                rank+=1;
                print = true;
            }
        }
        if (print){
            printf("\t(avec %d hérisson)\n",n);
        }
    }
}
