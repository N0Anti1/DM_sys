#include "logic.h"


// Il faut mieux vérifier que la case existe (au cas où)
// Et utilise les primitives de board !! (j'ai modifié déjà)
// donc : b->board[line][row].is_trap devient : board_is_trap(b, line, row)
bool verif_trap(board_t* b, int line, int row){
    if (board_is_trap(b, line, row)){
        for (int i = 0; i < row; i+=1){
            if (board_height(b, line, i) != 0){return false;}
            // On peut aussi faire de manière équivalente :
            if (board_height(b, line, i) != 0) return false;
        }
        return true; // inutile
    }
    return true;
}

// Utilise encore les primitives de board !!
bool is_playable_h(board_t* b, int line, int row){
    if (line < 0 || line >= HEIGHT || row < 0 || row >= WIDTH-1) return false;
    return (verif_trap(b, line, row) && (board_height(b, line, row) != 0));
}

// Tu n'utilises pas du tout les primitives !!!!
// Tu n'as 'pas le droit' d'utiliser le type cell_t
// mov : true=up ; false=down
bool is_playable_v(board_t* b, int line, int row, int player, bool mov){
    if (line < 0 || line >= HEIGHT || row < 0 || row >= WIDTH-1){return false;}
    if ((mov && line == 0) || (!mov && line == HEIGHT-1)){return false;}
    cell_t c = b->board[line][row];
    if (c.size == 0){return false;}
    return (verif_trap(b,line,row) && c.heap[c.size-1]==player+96);
}
// Exemple :
bool is_playable_v2(board_t* b, int line, int row, int player, bool mov) {
    if (line < 0 || line >= HEIGHT || row < 0 || row >= WIDTH-1) return false;
    if ((mov && line == 0) || (!mov && line == HEIGHT-1)) return false;
    if (board_height(b, line, row) == 0) return false;
    return verif_trap(b, line, row) && board_top(b, line, row) == (char)(player+65);
}

// Même problème, essaye de le changer toi-même pour t'entrainer
// Tu peux t'aider de ce qu'il y a dans board.h
// S'il te manque des choses c'est à Elisa de le faire
void play_h(board_t* b, int line, int row){
    cell_t c_init = b->board[line][row];
    cell_t c_end = b->board[line][row+1];
    char herisson = c_init.heap[c_init.size - 1];
    b->board[line][row].size -= 1;
    b->board[line][row+1].size += 1;
    b->board[line][row+1].heap[c_end.size] = herisson;
}

// Même problème, essaye de le changer toi-même pour t'entrainer
// mov : true=up ; false=down
void play_v(board_t* b, int line, int row, bool mov) {
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

// Il ne faudrait en théorie pas de b->...
// Mais tu n'as pas de primitive qui te revoie le i-ème elt de hh_end
// Donc comme c'est débile de faire une primitive juste pour ça je ne pense pas qu'on va enfaire
// Mais dans l'idée c'est interdit
bool is_game_end(board_t* b) {
    for (int i = 0; i < NB_PLAYER_MAX; i+=1){
        if (b->hh_end[i] == NB_HEDGEHOG-1){
            // print_classement(b);  Je préfère que ce soit le jeu qui gère quand afficher
            // Parce que peut-être qu'on veut clear l'affichage avant, ou autre...
            return true;
        }
        // Donc on peut remplacer par la ligne suivante équivalente :
        // if (b->hh_end[i] == NB_HEDGEHOG-1) return true;
    }
    return false;
}


// Tu vas avoir la deuxième place si tu es 3e et que les deux premiers font égalité
// Peut-être qu'il faut incrémenter le rang quand on print une équipe...
void print_classement(board_t* b) {
    int rank = 1;
    bool print = true;
    for (int n = NB_HEDGEHOG-1; n >= 0; n-=1){
        if (print){
            printf("Place %d : ",rank);
            print = false;
        }
        for (int i = 0; i < NB_PLAYER_MAX; i+=1){
            if (b->hh_end[i]==n){
                printf("équipe %c   ",(i+65));
                print = true;
            }
        }
        if (print){
            rank+=1;
            printf("(avec %d hérisson)\n",n);
        }
    }
}
