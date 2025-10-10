#include <string.h>
#include "logic.h"
#include <sys/ioctl.h>


const int NB_HERISSON = 2;
const int JOUEUR_MAX = 26;
const int LARGEUR = 3;
const int HAUTEUR = 3;
static char buffer[100];
static char trash[100];
static struct winsize w;
#define move_up 'm'
#define move_down 'b'
#define move_right 'd'
#define move_tutorial 't'
#define move_rules 'r'
#define move_option 'o'

enum langue {FRANCAIS, ENGLISH};



void scan() {
    buffer[0] = (char)0;
    trash[0] = (char)0;
    scanf("%s", buffer);
    scanf("%[^\n]", trash);
    printf("trash : %s\n", trash);
}

void clear_std() {
    fflush(stdout);
    if (system("clear") != 0) {
        system("cls");
    }
}

void print_center(char* text) {
    ioctl(0, TIOCGWINSZ, &w);
    int weight = w.ws_col;
    int diff = weight - strlen(text);

    if (diff >= 0) {
        for (int i = 0; i < diff/2; i ++) {
            printf(" ");
        }
        printf("%s\n", text);
        return;
    }
    
    for (int i = 0; i < weight; i ++) {
        printf("%c", text[i]);
    }
    printf("\n");
    print_center(&text[weight]);
}

void print_tutorial() {
    clear_std();
    printf("A chaque tour, le joueur dégigné doit entrer l'action qu'il souhaite faire.\n");
    printf("Les entrées valides sont de la forme : [A-%c][1-%d] 'mov'\n", (char)(LARGEUR + 64), HAUTEUR);
    printf("Le hérisson à la case désigné fera le déplacement 'mov'.\n");
    printf("'mov'=%c : monter\t'mov'=%c : descendre\t'mov'=%c : avancer\n", move_up, move_down, move_right);
    printf("\n'mov' est facultatif si vous avez déjà joué verticalement.\n");
    printf("\nSi une entrée est invalide, il vous sera redemandé de jouer.\n");
    printf("\n\nPour quitter le tutoriel, entrez qqch.\n");
    scan();
}

void print_rules() {
    clear_std();
    printf("Regardez le poly ou sur internet !!!!\n");
    printf("\n\nPour quitter les règles, entrez qqch.\n");
    scan();
}


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


void player_turn(board_t* b, int player, bool possible_v) {

    if (possible_v) {
        printf("Joueur %c, que veux-tu faire ?\n", (char)(player+65));
    }
    else {
        printf("Joueur %c, quel hérisson veux-tu avancer ?\n", (char)(player+65));
    }

    scan();
    int row = (int)buffer[0]-65;
    buffer[0] = '0';
    int line = string_to_ing(buffer)-1;
    char dir = trash[1];
    printf("%d,%d, |trash|=%ld\n", line, row, strlen(trash));

    // Check if the cell [line,row] exist
    if (row < 0 || row >= LARGEUR || line < 0 || line >= HAUTEUR) {
        printf("La case n'existe pas !\n");
        player_turn(b, player, possible_v);
    }
    // Check if the entry is correct
    if (!possible_v || (possible_v && strlen(trash) != 2)) {
        printf("L'entrée est incorrecte, regardez le tutoriel !\n");
        player_turn(b, player, possible_v);
    }
    // Check if the move is possible
    if (!possible_v && (dir == move_up || dir == move_down)) {
        printf("Tu ne peux plus jouer en vertical !!\n");
        player_turn(b, player, possible_v);
    }

    if (dir == move_up || dir == move_down) {
        if (is_playable_v(b, line, row, player, dir == move_up)) {
            play_v(b, line, row, dir == move_up);
            player_turn(b, player, false);
        }
        else {
            printf("Tu ne peux pas faire ce coup !\n");
            player_turn(b, player, possible_v);
        }
    }
    if (possible_v && dir != move_right) {
        printf("Précisez votre direction, vous avez encore du choix !\n");
        player_turn(b, player, possible_v);
    }
    if (is_playable_h(b, line, row)) {
        play_h(b, line, row);
        return;
    }
    printf("Tu ne peux pas faire ce coup !\n");
    player_turn(b, player, possible_v);
}

void play_game(int nb_player) {
    // board_t b = create_board();
    while(!is_game_end(NULL)) {
        for (int player = 0; player < nb_player; player += 1) {
            clear_std();
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

        printf("Options ('%c')\n", move_option);
        printf("\n\n\n");
        print_center("BIENVENUE sur le jeu Igel Ärgern");
        print_center("Le jeu de course de hérisson !!\n");
        printf("Jouer (entrez le nombre de joueur (entre 2 et 26))\n");
        printf("Tutoriel ('%c')\n", move_tutorial);
        printf("Règles ('%c')\n", move_rules);
        printf("Quitter ('q')\n");
        
        scan();
        

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
