#include "logic.h"


#ifndef BOT_H
#define BOT_H

#define NB_COUPS_MAX (HEIGHT*(WIDTH-1))

typedef struct bot {
    char player;
    int coups_jouables[NB_COUPS_MAX][2];
    int nb_coups;
} bot_t;

bot_t init_bot (char player);

void coups_jouables_vu(bot_t* ia, board_t* b); //modifie le tab coups_jouables et nb_coups par les coups jouables verticalement vers le haut par player
void coups_jouables_vd(bot_t* ia, board_t* b); //pareil  vers le bas
void coups_jouables_h(bot_t* ia, board_t* b, int line);  //pareil horizontalement

void play_bot_v(bot_t* ia, board_t* b, bool mov);
void play_bot_h(bot_t* ia, board_t* b, int line);

void bot_turn(bot_t* ia, board_t* b);

#endif
