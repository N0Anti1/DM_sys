#include "logic.h"


static char buffer[10];
static char trash[10];
static struct winsize w;


enum langue {FRANCAIS, ENGLISH};



void scan() {
    buffer[0] = (char)0;
    trash[0] = (char)0;
    scanf("%s", buffer);
    scanf("%[^\n]", trash);
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
    printf("Les entrées valides sont de la forme : [A-%c][1-%d] 'mov'\n", (char)(WIDTH + 64), HEIGHT);
    printf("Le hérisson à la case désigné fera le déplacement 'mov'.\n");
    printf("'mov'=%c : monter\t'mov'=%c : descendre\t'mov'=%c : avancer\n", MOVE_up, MOVE_down, MOVE_right);
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
    for (int i = 0; i < (int)strlen(s); i += 1) {
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


void player_turn(board_t* b, int player, bool possible_v, int highlighted_line) {

    if (possible_v) {
        printf("Joueur %c, que veux-tu faire ?\n", (char)(player+65));
        if (is_line_empty(b, highlighted_line)) {
            printf("Vous pouvez passer votre tour en entrant 'skip'\n");
        }
    }
    else {
        if (is_line_empty(b, highlighted_line)) {
            printf("Vous ne pouvez pas jouer sur la ligne %d.\n", highlighted_line+1);
            printf("Entrez qqch pour passer votre tour\n");
            scan();
            return;
        }
        printf("Joueur %c, quel hérisson veux-tu avancer (sur la ligne %d) ?\n", (char)(player+65), highlighted_line+1);
    }

    scan();
    if (is_line_empty(b, highlighted_line) && strcmp(buffer, "skip") == 0) {
        return;
    }
    int row = (int)buffer[0]-65;
    buffer[0] = '0';
    int line = string_to_ing(buffer)-1;
    char dir = trash[1];
    
    // Check if the cell [line,row] exist
    if (row < 0 || row >= WIDTH || line < 0 || line >= HEIGHT) {
        // Check if the row input is in lowercase
        if (line >= 0 && line < HEIGHT && row >= 32 && row < WIDTH+32) row -= 32;
        else {
            printf("La case n'existe pas !\n");
            player_turn(b, player, possible_v, highlighted_line);
            return;
        }
    }
    // Check if the entry is correct
    if (strlen(trash) != 2) {
        printf("L'entrée est incorrecte, regardez le tutoriel !\n");
        player_turn(b, player, possible_v, highlighted_line);
        return;
    }
    // Check if the move is possible
    if (!possible_v && (dir == MOVE_up || dir == MOVE_down)) {
        printf("Tu ne peux plus jouer en vertical !!\n");
        player_turn(b, player, possible_v, highlighted_line);
        return;
    }

    if (dir == MOVE_up || dir == MOVE_down) {
        if (is_playable_v(b, line, row, player, dir == MOVE_up)) {
            play_v(b, line, row, dir == MOVE_up);
            clear_std();
            board_print(b, highlighted_line);
            printf("Le dé à réalisé un %d\n", highlighted_line+1);
            player_turn(b, player, false, highlighted_line);
        }
        else {
            printf("Tu ne peux pas faire ce coup !\n");
            player_turn(b, player, possible_v, highlighted_line);
        }
        return;
    }
    
    
    if (possible_v && dir != MOVE_right) {
        printf("Précisez votre direction, vous avez encore du choix !\n");
        player_turn(b, player, possible_v, highlighted_line);
        return;
    }
    
    if (line == highlighted_line) {
        if (is_playable_h(b, line, row)) {
            play_h(b, line, row);
            return;
        }
    }
    else {
        printf("Tu dois jouer sur la ligne %d !!", highlighted_line+1);
        player_turn(b, player, possible_v, highlighted_line);
        return;
    }

    printf("Tu ne peux pas faire ce coup !\n");
    player_turn(b, player, possible_v, highlighted_line);
    return;
}


void play_game(int nb_player) {
    board_t b = create_board();
    init_board(&b, nb_player);

    while(!is_game_end(&b)) {
        for (int player = 0; player < nb_player; player += 1) {
            int de = rand() % HEIGHT + 1;
            clear_std();
            board_print(&b, de-1);
            printf("Le dé à réalisé un %d\n", de);
            player_turn(&b, player, true, de-1);
        }
    }
    clear_std();
    print_center("Fin de la partie !!!");
    printf("\nVoici le classement :\n");
    print_classement(&b, nb_player);
    printf("\nEntrez qqch pour continuer\n");
    scan();
}


int main() {
    srand(time(NULL));

    bool running = true;

    while (running)
    {
        clear_std();

        printf("Options ('%s')\n", MOVE_option);
        printf("\n\n\n");
        print_center("BIENVENUE sur le jeu Igel Ärgern");
        print_center("Le jeu de course de hérisson !!\n");
        printf("Jouer (entrez le nombre de joueur [2-26])\n");
        printf("Tutoriel ('%s')\n", MOVE_tutorial);
        printf("Règles ('%s')\n", MOVE_rules);
        printf("Quitter ('q')\n");
        
        scan();
        
        int nb_player = string_to_ing(buffer);
        if (strcmp(buffer, MOVE_tutorial) == 0) {
            print_tutorial();
        }
        else if (strcmp(buffer, MOVE_rules) == 0) {
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
