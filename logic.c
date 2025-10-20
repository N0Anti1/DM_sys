#include "logic.h"



bool verif_not_traped(board_t* b, int line, int row) {
    if (board_is_trap(b, line, row) && board_height(b, line, row) == 1) {
        for (int i = row-1 ; i >= 0 ; i-=1) {
            if (board_height(b, line, i) != 0) { return false; }
            if (board_has_wall(b, line, i)) { break; }
        }
    }
    return true;
}

bool is_playable_h(board_t* b, int line, int row) {
    if (line < 0 || line >= get_height(b) || row < 0 || row >= get_width(b)-1) { return false; }
    if (board_has_wall(b, line, row+1)) { return false; }
    return (verif_not_traped(b, line, row) && (board_height(b, line, row) != 0 ));
}

bool is_playable_v(board_t* b, int line, int row, int player, bool mov) {
    if (line < 0 || line >= get_height(b) || row < 0 || row >= get_width(b)-1) { return false; }
    if ((mov && line == 0) || (!mov && line == get_height(b)-1)) { return false; }
    if (board_height(b, line, row) == 0) { return false; }
    return (verif_not_traped(b, line, row) && board_top(b, line, row) == (char)(player + 65));
}



void play_h(board_t* b, int line, int row) {
    assert(line >= 0 && line < get_height(b) && row >= 0 && row < get_width(b)-1);
    char player = board_pop(b, line, row);
    board_push(b, line, row+1, player);
    if (row == get_width(b)-2) { b->hh_end[((int)player)-65] += 1; }
}

void play_v(board_t* b, int line, int row, bool mov) {
    assert(mov <= line && line < get_height(b) - !mov && 0 <= row && row < get_width(b));
    if (mov) { board_push(b, line-1, row, board_pop(b, line, row)); }
    else { board_push(b, line+1, row, board_pop(b, line, row)); }
}


// True if a horizontal move is possible on the line
bool is_line_playable(board_t* b, int line) {
    assert(0 <= line && line < get_height(b));
    for (int i = 0; i < get_width(b) - 1 ; i += 1) {
        if (board_height(b, line, i) > 0 && !board_has_wall(b, line, i+1)) return true;
    }
    return false;
}

bool is_game_end(board_t* b) {
    for (int i = 0; i < NB_PLAYER_MAX; i+=1) {
        if (b->hh_end[i] >= get_nb_hedgehog(b) - 1) {
            return true;
        }
    }
    return false;
}


void print_ranking(board_t* b, int nb_player) {
    int rank = 1;
    bool print = true;
    for (int n = get_nb_hedgehog(b); n >= 0 && rank <= nb_player; n-=1) {
        if (print) {
            printf("- Place #%d :", rank);
            print = false;
        }
        for (int i = 0; i < nb_player; i+=1) {
            if (b->hh_end[i]==n) {
                printf("%s équipe %c", print ? "," : "", (i+65));
                rank+=1;
                print = true;
            }
        }
        if (print) {
            printf("\t(avec %d hérisson)\n", n);
        }
    }
}

