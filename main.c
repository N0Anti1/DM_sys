#include <string.h>
#include "logic.h"


const int NB_HERISSON = 2;
const int JOUEUR_MAX = 26;
const int LARGEUR = 3;
const int HAUTEUR = 3;
static char buffer[100];
#define up 'm'
#define down 'b'
#define right 'd'



// return -1 if (s != int)
int string_to_ing(char* s) {
    int res = 0;
    for (int i = 0; i < strlen(s); i += 1) {
        if (48 <= (int)s[i] && (int)s[i] <= 57) {
            res *= 10;
            res += (int)s[i]-48;
        }
        else {
            return -1;
        }
    }
    return res;
}


void clear_std() {
    fflush(stdout);
    // if (system("clear") != 0) {
    //     system("cls");
    // }
}
void scan() {
    for (int i = 0; i < 100; i ++) {
        buffer[i] = (char)1;
    }
    scanf("%s", buffer);
    char* reste;
    scanf("%[^\n]", reste);
}

void player_turn(board_t* b, int player, bool possible_v) {

    if (possible_v) {
        printf("Joueur %c, que veux-tu faire ?\n", (char)(player+65));
        scanf("%s %c", buffer, &buffer[5]);
        char* reste;
        scanf("%[^\n]", reste);
    }
    else {
        printf("Joueur %c, quel hérisson veux-tu avancer ?\n", (char)(player+65));
        scan();
    }

    int row = (int)buffer[0]-65;
    char possible_int[99];
    int next = 1;
    for (int i = 0; i < 100; i += 1) {
        if (buffer[i+1] == ' ') {
            possible_int[i] = '\0';
            break;
        }
        possible_int[i] = buffer[i+1];
        next += 1;
    }
    int line = string_to_ing(possible_int)-1;
    char dir = buffer[5];
    printf("%d,%d,%c\n", line, row, dir);

    if (row < 0 || row >= LARGEUR) return;
    if (line < 0 || line >= HAUTEUR) return;
    if (dir == up && possible_v) {
        if (is_playable_v(b, line, row, player, true)) {
            play_v(b, line, row, true);
            player_turn(b, player, false);
        }
        else {
            printf("Tu ne peux pas jouer ici !\n");
        }
    }
    else if (dir == down && possible_v) {
        if (is_playable_v(b, line, row, player, false)) {
            play_v(b, line, row, false);
            player_turn(b, player, false);
        }
        else {
            printf("Tu ne peux pas jouer ici !\n");
        }
    }
    else if (!possible_v && (dir == up || dir == down)) {
        printf("Tu ne peux plus jouer en vertical !!!\n");
        player_turn(b, player, possible_v);
    }
    else if (dir != right && possible_v) {
        printf("Précisez votre direction, vous avez encore du choix !\n");
        player_turn(b, player, possible_v);
    }
    else {
        if (is_playable_h(b, line, row)) play_h(b, line, row);
        else printf("Tu ne peux pas jouer ici !\n");
    }

}

void print_tutorial() {
    clear_std();
    printf("A chaque tour, le joueur dégigné doit entrer l'action qu'il souhaite faire.\n");
    printf("Les entrées valides sont de la forme : [A-%c][1-%d] 'mov'\n", (char)(LARGEUR + 64), HAUTEUR);
    printf("Le hérisson à la case désigné fera le déplacement 'mov'.\n");
    printf("'mov'=%c : monter\t'mov'=%c : descendre\t'mov'=%c : avancer\n", up, down, right);
    printf("\n'mov' est facultatif si vous avez déjà joué verticalement.\n");
    printf("\nSi une entrée est invalide, il vous sera redemandé de jouer.\n");
    printf("\n\nPour quitter le tutoriel, entrez qqch.\n");
    scanf("%s", buffer);
}

void print_rules() {
    clear_std();
    printf("Regardez le poly ou sur internet !!!!\n");
    printf("\n\nPour quitter les règles, entrez qqch.\n");
    scanf("%s", buffer);
}


void play_game(int nb_player) {
    // board_t b = create_board();
    clear_std();
    while(!is_game_end(NULL)) {
        for (int player = 0; player < nb_player; player += 1) {
            // board_print(b, line);
            player_turn(NULL, player, true);
        }
    }
    printf("Fin de la partie, entrée qqch pour continuer\n");
    scanf("%[^\n]", buffer);
}


int main() {
    bool running = true;
 
    while (running)
    {
        clear_std();

        printf("Options ('o')\n\n\n\n\t\tBIENVENUE sur le jeu Igel Ärgern\n\t\tLe jeu de course de hérisson !!\n\n");
        printf("Pour jouer, entrez le nombre de joueur (entre 2 et 26)\n");
        printf("Tutoriel ('t')\n");
        printf("Règles ('r')\n");
        printf("Quitter ('q')\n");
        
        scanf("%[^\n]", buffer);
        

        int nb_player = string_to_ing(buffer);
        if (strcmp(buffer, "t") == 0) {
            print_tutorial();
        }
        else if (strcmp(buffer, "r") == 0) {
            print_rules();
        }
        else if (2 <= nb_player && nb_player <= 26) {
            play_game(nb_player);
        }
        else {
            running = false;
        }
    }
    

    return 0;
}
