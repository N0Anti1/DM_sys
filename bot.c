#include "bot.h"


bot_t init_bot (int player) {
    bot_t ia;
    ia.player = player;
    ia.nb_moves = 0;
    return ia;
}


void playable_moves_v(bot_t* ia, board_t* b, bool mov) {
    ia->nb_moves = 0;
    for (int line = 0; line < get_height(b); line += 1) {
        for (int row = 0; row < get_width(b) - 1; row += 1) {
            if (is_playable_v(b, line, row, ia->player, mov)) {
                ia->playable_moves[ia->nb_moves][0] = line;
                ia->playable_moves[ia->nb_moves][1] = row;
                ia->nb_moves += 1;
            }
        }
    }
}

void playable_moves_h(bot_t* ia, board_t* b, int line) {
    ia->nb_moves = 0;
    for (int row = 0; row < get_width(b) - 1; row += 1) {
        if (is_playable_h(b, line, row)) {
            ia->playable_moves[ia->nb_moves][0] = line;
            ia->playable_moves[ia->nb_moves][1] = row;
            ia->nb_moves += 1;
        }
    }
}


bool play_bot_v(bot_t* ia, board_t* b, bool mov) {
    playable_moves_v(ia, b, mov);
    if (ia->nb_moves != 0) {
        int move = rand() % ia->nb_moves;
        int line = ia->playable_moves[move][0], row = ia->playable_moves[move][1];
        play_v(b, line, row, mov);
        
        ia->played_move[0][0] = line;
        ia->played_move[0][1] = row;
        return true;
    }
    return false;
}

void play_bot_h(bot_t* ia, board_t* b, int line) {
    playable_moves_h(ia, b, line);
    if (ia->nb_moves != 0) {
        int move = rand() % ia->nb_moves;
        int row = ia->playable_moves[move][1];
        play_h(b, line, row);
        
        ia->played_move[1][0] = line;
        ia->played_move[1][1] = row;
    }
}


bool bot_turn(bot_t* ia, board_t* b, int line) {
    int pv = rand() % 3; // pv=0 -> up, pv=1 -> down, pv=2 -> skip
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
    /**
     * @param mov : true iff the bot has played a vertical move. That implies 'dir' and 'start'
     * @param dir : true iff the vertical move is 'up'
     * @param start : a move touch two cells : the start of the move and it's end. It's true iff the cell is the start
     */

    if (slice == 0) {   // Same code as cell_print with arrow to show the bot move
        char ext = cell_is_trap(c) ? 'V' : '-';
        char in = ext;
        if (mov && dir && start) in = '|';
        else if (mov && !dir && !start) in = 'V';

        printf(" %c%c%c ", ext, in, ext);
    }
    else if (slice == 1) {  // Same code as cell_print
        cell_print(c, slice, false);
    }
    else if (slice == 2) {  // Same code as cell_print
        cell_print(c, slice, false);
    }    
    else if (slice == 3) {  // Same code as cell_print with arrow to show the bot move
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
    for (int line = -1; line <= get_height(b); line += 1) {
        for (int slice = 0; slice < 4; slice += 1) {
            for (int row = -1; row < get_width(b); row += 1) {

                if (line == -1) {
                    if (row == -1) printf("     ");
                    else if (slice == 0 && row == 0) printf(" START ");
                    else if (slice == 0 && row == get_width(b) - 1) printf("FINISH ");
                    else if (slice == 0 || slice == 1) printf("       ");
                    else if (slice == 2) printf("  row  ");
                    else if (slice == 3) printf("   %c   ", (char)(row+97));
                }

                else if (line < get_height(b)) {
                    if (row == -1 && slice == 1) printf("line ");
                    else if (row == -1 && slice == 2) printf("  %d  ", line+1);
                    else if (row == -1) printf("     ");
                    else {
                        if (slice == 1 && ia->played_move[1][1] == row-1 && ia->played_move[1][0] == line) {
                            printf(">");
                        }
                        else printf("%s", board_has_wall(b, line, row) ? "▒" : " ");
                        // Check if the cell is connected to the bot move
                        if (ia->played_move[0][1] == row && ia->played_move[0][0] == line) {
                            cell_print_bot(&(b->board[line][row]), slice, true, dir, ia->played_move[0][0] == line);
                        }
                        else if (ia->played_move[0][1] == row && ia->played_move[0][0] + !dir == line + dir) {
                            cell_print_bot(&(b->board[line][row]), slice, true, dir, ia->played_move[0][0] == line);
                        }
                        else cell_print_bot(&(b->board[line][row]), slice, false, dir, false);
                        if (slice == 1 && ia->played_move[1][1] == row && ia->played_move[1][0] == line) {
                            printf("-");
                        }
                        else printf(" ");
                    }
                }

                else if (line == get_height(b)) {
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

