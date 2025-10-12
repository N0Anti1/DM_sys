#include "logic.h"

const int nb_joueurs = 4;
const int nb_herissons = 6;
const int nb_line = 6;
const int nb_row = 9;

void print_classement(board_t* b){
    int rank = 1;
    bool print = true;
    for (int n = nb_herissons-1; n >= 0; n-=1){
        if (print){
            printf("Place %d : ",rank);
            print = false;
        }
        for (int i = 0; i < nb_joueurs; i+=1){
            if (b->hh_end[i]==n){
                printf("équipe %c   ",(i+97));
                print = true;
            }
        }
        if (print){
            rank+=1;
            printf("(avec %d hérisson)\n",n);
        }
    }
}

bool is_game_end(board_t* b){
    for (int i = 0; i < nb_joueurs; i+=1){
        if (b->hh_end[i] == nb_herissons-1){
            print_classement(b);
            return true;
        }
    }
    return false;
}

bool verif_trap(board_t* b, int line, int row){
    if (b->board[line][row].is_trap){
        for (int i = 0; i < row; i+=1){
            if (b->board[line][i].size != 0){return false;}
        }
        return true;
    }
    return true;
}

bool is_playable_h(board_t* b, int line, int row){
    if (line < 0 || line >= nb_line || row < 0 || row >= nb_row-1){return false;}
    return (verif_trap(b,line,row) && (b->board[line][row].size != 0));
}

// mov : true=up ; false=down
bool is_playable_v(board_t* b, int line, int row, int player, bool mov){
    if (line < 0 || line >= nb_line || row < 0 || row >= nb_row-1){return false;}
    if ((mov && line == 0) || (!mov && line == nb_line-1)){return false;}
    cell_t c = b->board[line][row];
    if (c.size == 0){return false;}
    return (verif_trap(b,line,row) && c.heap[c.size-1]==player+96);
}

void play_h(board_t* b, int line, int row){
    cell_t c_init = b->board[line][row];
    cell_t c_end = b->board[line][row+1];
    char herisson = c_init.heap[c_init.size - 1];
    b->board[line][row].size -= 1;
    b->board[line][row+1].size += 1;
    b->board[line][row+1].heap[c_end.size] = herisson;
}

// mov : true=up ; false=down
void play_v(board_t* b, int line, int row, bool mov){
    cell_t c_init = b->board[line][row];
    char herisson = c_init.heap[c_init.size-1];
    b->board[line][row].size -= 1;
    if (mov){
        cell_t c_end = b->board[line-1][row];
        b->board[line-1][row].size += 1;
        b->board[line-1][row].heap[c_end.size] = herisson;
    }
    else{
        cell_t c_end = b->board[line+1][row];
        b->board[line+1][row].size += 1;
        b->board[line+1][row].heap[c_end.size] = herisson;
    }
}
