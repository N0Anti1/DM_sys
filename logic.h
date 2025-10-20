#include "board.h"


#ifndef LOGIC_H
#define LOGIC_H

// Return true if the hh is not trap
bool verif_not_traped(board_t* b, int line, int row);
// Check if a move is possible
bool is_playable_h(board_t* b, int line, int row);
bool is_playable_v(board_t* b, int line, int row, int player, bool mov);    // mov : true=up ; false=down

// Play a move
void play_h(board_t* b, int line, int row);
void play_v(board_t* b, int line, int row, bool mov);

bool is_line_playable(board_t* b, int line);
bool is_game_end(board_t* b);

void print_ranking(board_t* b, int nb_player);

#endif
