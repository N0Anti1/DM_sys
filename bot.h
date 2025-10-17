#include "logic.h"


#ifndef BOT_H
#define BOT_H

#define NB_MAX_MOVES (HEIGHT*(WIDTH-1))

typedef struct bot {
    int player;
    int playable_moves[NB_MAX_MOVES][2];
    int nb_moves;
    int played_move[2][2];
} bot_t;

bot_t init_bot(int player);

void playable_moves_vu(bot_t* ia, board_t* b); //modifie le tab playable_moves et nb_moves par les coups jouables verticalement vers le haut par player
void playable_moves_vd(bot_t* ia, board_t* b); //pareil  vers le bas
void playable_moves_h(bot_t* ia, board_t* b, int line);  //pareil horizontalement

bool play_bot_v(bot_t* ia, board_t* b, bool mov);
void play_bot_h(bot_t* ia, board_t* b, int line);

// return true if a vertical move is play
bool bot_turn(bot_t* ia, board_t* b, int line);

void cell_print_bot(cell_t* c, int slice, bool mov, bool dir, bool start);
void board_print_bot(board_t* b, bot_t* ia, bool dir);

#endif
