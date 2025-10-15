#include "bot.h"


bot_t init_bot (char player){
    bot_t ia;
    ia.player = player;
    ia.nb_coups = 0;
    return ia;
}

void coups_jouables_vu(bot_t* ia, board_t* b){
    for (int row = 0; row < WIDTH-1; row+=1){
        for (int line = 0; line < HEIGHT; line+=1){
            if (is_playable_v(b, line, row, ia->player, true)){
                ia->coups_jouables[ia->nb_coups][0] = row;
                ia->coups_jouables[ia->nb_coups][1] = line;
                ia->nb_coups += 1;
            }
        }
    }
}

void coups_jouables_vd(bot_t* ia, board_t* b){
    for (int row = 0; row < WIDTH-1; row+=1){
        for (int line = 0; line < HEIGHT; line+=1){
            if (is_playable_v(b, line, row, ia->player, false)){
                ia->coups_jouables[ia->nb_coups][0] = row;
                ia->coups_jouables[ia->nb_coups][1] = line;
                ia->nb_coups += 1;
            }
        }
    }
}

void coups_jouables_h(bot_t* ia, board_t* b, int line){
    for (int row = 0; row < WIDTH-1; row+=1){
            if (is_playable_h(b, line, row)){
                ia->coups_jouables[ia->nb_coups][0] = row;
                ia->coups_jouables[ia->nb_coups][1] = line;
                ia->nb_coups += 1;
            }
        }
}

void play_bot_v(bot_t* ia, board_t* b, bool mov){
    if (mov) {coups_jouables_vu(ia, b);}
    else {coups_jouables_vd(ia, b);}
    if(ia->nb_coups != 0){
        int rd = rand() % ia->nb_coups;
        int coups[2]; coups[0] = ia->coups_jouables[rd][0]; coups[1] = ia->coups_jouables[rd][1];
        play_v(b, coups[1], coups[0], mov);
        ia->nb_coups = 0;
    }
    else {printf("bot %c n'a pas joué v\n",ia->player);}
}

void play_bot_h(bot_t* ia, board_t* b, int line){
    coups_jouables_h(ia, b, line);
    if (ia->nb_coups != 0){
        int rd = rand() % ia->nb_coups;
        int coups[2]; coups[0] = ia->coups_jouables[rd][0]; coups[1] = ia->coups_jouables[rd][1];
        play_h(b, coups[1], coups[0]);
        ia->nb_coups = 0;
    }
    else {printf("bot %c n'a pas joué h\n",ia->player);}
}

void bot_turn(bot_t* ia, board_t* b){
    int line = rand () % HEIGHT; //ligne a jouer
    int pv = rand() % 3; // pv=0 -> up, pv=1 -> down, pv=2 -> passe
    if (pv == 0){play_bot_v(ia, b, true); board_print(b, line);}
    else if (pv == 1){play_bot_v(ia, b, false); board_print(b, line);}
    else if (pv == 2){printf("bot %c n'a pas joué v\n",ia->player);}

    play_bot_h(ia, b, line);
}
