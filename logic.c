#include "logic.h"

bool is_playable_h(board_t* b, int line, int row) {
    return true;
}
bool is_playable_v(board_t* b, int line, int row, int player, bool mov) {
    return true;
}
// Play a move
void play_h(board_t* b, int line, int row) {
    printf("playH\n");
}
void play_v(board_t* b, int line, int row, bool mov) {
    printf("playV\n");
}

bool is_game_end(board_t* b) {
    return false;
}