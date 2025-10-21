#include "logic.h"
#include "bot.h"


static char buffer[100];
static char trash[100];
static struct winsize w;


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

int min(int a, int b) {
    return b < a ? b : a;
}

// Return -1 if (s != int)
int string_to_ing(char* s) {
    int res = 0;
    for (int i = 0; i < (int)strlen(s); i += 1) {
        if (48 <= (int)s[i] && (int)s[i] <= 57) {
            res *= 10;
            res += (int)s[i] - 48;
        }
        else {
            return -1;
        }
    }
    return res;
}

// Print a text centered in the console
void print_center(char* text) {
    ioctl(0, TIOCGWINSZ, &w);
    int weight = w.ws_col;
    int diff = weight - strlen(text);

    if (diff >= 0) {
        for (int i = 0; i < diff/2; i += 1) {
            printf(" ");
        }
        printf("%s\n", text);
        return;
    }
    
    for (int i = 0; i < weight; i += 1) {
        printf("%c", text[i]);
    }
    printf("\n");
    print_center(&text[weight]);
}


void print_tutorial(int w, int h) {
    clear_std();
    print_center("Igel Ärgern");
    print_center("TUTORIEL\n");
    printf("A chaque tour, le joueur dégigné doit entrer l'action qu'il souhaite faire.\n");
    printf("Les entrées valides sont de la forme : [A-%c][1-%d] 'mov'\n", (char)(w + 64), h);
    printf("Le hérisson à la case désigné fera le déplacement 'mov'.\n");
    printf("'mov'=%c : monter\t'mov'=%c : descendre\t'mov'=%c : avancer\n", MOVE_up, MOVE_down, MOVE_right);
    printf("\n'mov' est facultatif si vous avez déjà joué verticalement.\n");
    printf("\nSi une entrée est invalide, il vous sera redemandé de jouer.\n");
    printf("\n\nPour quitter le tutoriel, entrez qqch.\n");
    scan();
}

void print_rules() {
    clear_std();
    print_center("Igel Ärgern");
    print_center("RÈGLES\n");
    printf("Vous avez des hérissons à amener sur la ligne d'arrivée.\n");
    printf("A chaque tour chaque joueur peut déplacer verticalement l'un de ses hérissons, puis avance l'un des hérissons d'une case au hasard désignée par un dé.\n");
    printf("On ne peut déplacer que les hérissons au dessus de leur case.\n");
    printf("Le jeu se termine s'il manque au plus un hérisson à un joueur sur la ligne d'arrivée à la fin d'un tour.\n");
    printf("\nLes cases piégées ne peuvent se vider que s'il n'y a aucun hérisson sur les cases à sa gauche (jusqu'au prochain mur).\n");
    printf("\n\nPour quitter les règles, entrez qqch.\n");
    scan();
}

void print_option(int* width, int* height, int* nb_hedgehog, int* trap, int* wall, int* nb_bot) {
    clear_std();
    print_center("Igel Ärgern");
    print_center("OPTION\n");
    printf("Voici les commandes :\n");
    printf("Déplacement vers le haut : '%c'\n", MOVE_up);
    printf("Déplacement vers le bas : '%c'\n", MOVE_down);
    printf("Déplacement vers la droite : '%c'\n", MOVE_right);

    printf("\n\nLargeur du plateau : %d\t\t\t(entre 3 et %d)\n", *width, WIDTH_MAX);
    printf("Hauteur du plateau : %d\t\t\t(entre 2 et %d)\n", *height, HEIGHT_MAX);
    printf("Nombre de hérissons par joueur : %d\t(entre 2 et %d)\n", *nb_hedgehog, NB_HEDGEHOG_MAX);

    printf("\nPourcentage de pièges : %d%%\t\t(entre 0 et 100)\n", *trap);
    printf("Pourcentage de murs : %d%%\t\t(entre 0 et 100)\n", *wall);

    printf("\nNombre de bot : %d\t\t\t(entre 0 et %d)\n", *nb_bot, NB_PLAYER_MAX);

    printf("\n\nVoici une idée de la largeur du plateau : (il doit n'y avoir qu'une seule ligne)\n");
    for (int i = 0; i < 7 * (*width) + 5; i += 1) {
        printf("#");
    }
    printf("\n");

    printf("\n\nPour changer un paramètre, entrez son mot-clé suivi de la nouvelle valeur\n");
    printf("(liste des mots-clé : 'width', 'height', 'hedgehog', trap', 'wall', 'bot')\n");
    printf("\nPour quitter les options, entrez qqch.\n");

    scan();
    int n = string_to_ing(&(trash[1]));
    // Manages parameter change
    if (strcmp(buffer, "width") == 0) {
        if (3 <= n && n <= WIDTH_MAX) {
            *width = n;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
    else if (strcmp(buffer, "height") == 0) {
        if (2 <= n && n <= HEIGHT_MAX) {
            *height = n;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
    else if (strcmp(buffer, "hedgehog") == 0) {
        if (2 <= n && n <= NB_HEDGEHOG_MAX) {
            *nb_hedgehog = n;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
    else if (strcmp(buffer, "trap") == 0) {
        if (0 <= n && n <= 100) {
            *trap = n;
            if (*trap + *wall > 100) *wall = 100 - *trap;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
    else if (strcmp(buffer, "wall") == 0) {
        if (0 <= n && n <= 100) {
            *wall = n;
            if (*trap + *wall > 100) *trap = 100 - *wall;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
    else if (strcmp(buffer, "bot") == 0) {
        if (0 <= n && n <= NB_PLAYER_MAX) {
            *nb_bot = n;
        }
        print_option(width, height, nb_hedgehog, trap, wall, nb_bot);
    }
}
// Return true if the game is aborted
bool print_option_ingame() {
    clear_std();
    print_center("Igel Ärgern");
    print_center("OPTION");
    printf("\nVoici les commandes :\n");
    printf("Déplacement vers le haut : '%c'\n", MOVE_up);
    printf("Déplacement vers le bas : '%c'\n", MOVE_down);
    printf("Déplacement vers la droite : '%c'\n", MOVE_right);
    printf("\n\nPour arrêter la partie, entrez 'quit'.\n");
    printf("Pour quitter les options, entrez qqch.\n");
    scan();
    if (strcmp(buffer, "quit") == 0) return true;
    return false;
}


bool check_input(board_t* b, bool possible_v, int line, int* row, char dir) {
    // Check if the cell [line, row] exist
    if (*row < 0 || *row >= get_width(b) || line < 0 || line >= get_height(b)) {
        // Check if the row input is in lowercase
        if (line >= 0 && line < get_height(b) && *row >= 32 && *row < get_width(b)+32) *row -= 32;
        else {
            printf("La case n'existe pas !\n");
            return false;
        }
    }

    // Check if the entry is correct
    if (strlen(trash) != 2) {
        printf("L'entrée est incorrecte, regardez le tutoriel !\n");
        return false;
    }

    // Check if the move is possible
    if (!possible_v && (dir == MOVE_up || dir == MOVE_down)) {
        printf("Tu ne peux plus jouer en vertical !!\n");
        return false;
    }

    return true;
}

bool player_turn(board_t* b, int player, bool possible_v, int highlighted_line) {
    /**
     * Manages a player's turn
     * @param possible_v : describe if the player can play in vertical
     * @return true if the turn is end, false if the game is aborted
     */
    
    if (possible_v) {
        printf("Joueur %c, que veux-tu faire ?\n", (char)(player+65));
        if (!is_line_playable(b, highlighted_line)) {
            printf("Vous pouvez passer votre tour en entrant 'skip'\n");
        }
    }
    else {
        if (!is_line_playable(b, highlighted_line)) {
            printf("Vous ne pouvez pas jouer sur la ligne %d.\n", highlighted_line+1);
            printf("Entrez qqch pour passer votre tour\n");
            scan();
            return true;
        }
        printf("Joueur %c, quel hérisson veux-tu avancer (sur la ligne %d) ?\n", (char)(player+65), highlighted_line+1);
    }

    scan();
    if (!is_line_playable(b, highlighted_line) && strcmp(buffer, "skip") == 0) {
        return true;
    }
    int row = (int)buffer[0]-65;
    buffer[0] = '0';
    int line = string_to_ing(buffer)-1;
    char dir = trash[1];

    // Check if 'option' is selected
    if (row+65 == (int)'o' && (int)strlen(buffer) == 1 && (int)strlen(trash) == 0) {
        bool quit = print_option_ingame();
        if (!quit) {
            clear_std();
            board_print(b, highlighted_line);
            printf("Le dé à réalisé un %d\n", highlighted_line + 1);
            return player_turn(b, player, possible_v, highlighted_line);
        }
        return false;
    }
    // Check if 'tuto' is selected
    else if (row+65 == (int)'t' && (int)strlen(buffer) == 1 && (int)strlen(trash) == 0) {
        print_tutorial(get_width(b), get_height(b));
        clear_std();
        board_print(b, highlighted_line);
        printf("Le dé à réalisé un %d\n", highlighted_line+1);
        return player_turn(b, player, possible_v, highlighted_line);
    }
    
    // Check if the input is correct
    if (!check_input(b, possible_v, line, &row, dir)) {
        return player_turn(b, player, possible_v, highlighted_line);
    }

    // If it's a vertical move
    if (dir == MOVE_up || dir == MOVE_down) {
        if (is_playable_v(b, line, row, player, dir == MOVE_up)) {
            play_v(b, line, row, dir == MOVE_up);
            clear_std();
            board_print(b, highlighted_line);
            printf("Le dé à réalisé un %d\n", highlighted_line+1);
            return player_turn(b, player, false, highlighted_line);
        }
        else {
            printf("Tu ne peux pas faire ce coup !\n");
            return player_turn(b, player, possible_v, highlighted_line);
        }
    }

    if (possible_v && dir != MOVE_right) {
        printf("Précisez votre direction, vous avez encore du choix !\n");
        return player_turn(b, player, possible_v, highlighted_line);
    }
    
    // It's a horizontal move
    if (line == highlighted_line) {
        if (is_playable_h(b, line, row)) {
            play_h(b, line, row);
            return true;
        }
    }
    else {
        printf("Tu dois jouer sur la ligne %d !!\n", highlighted_line+1);
        return player_turn(b, player, possible_v, highlighted_line);
    }

    // It's not a legal move :
    printf("Tu ne peux pas faire ce coup !\n");
    return player_turn(b, player, possible_v, highlighted_line);
}


void play_game(int width_board, int height_board, int nb_hedgehog, int nb_player, int nb_bot, int prop_trap, int prop_wall) {
    board_t board = create_board(width_board, height_board, nb_hedgehog, prop_trap / 100., prop_wall / 100.);
    board_t* b = &board;
    init_board(b, nb_player+nb_bot);

    bot_t bots[NB_PLAYER_MAX];
    for (int i = 0; i < nb_bot; i += 1) {
        bots[i] = init_bot(nb_player+i);
    }

    while (!is_game_end(b)) {
        for (int player = 0; player < nb_player; player += 1) {
            int de = rand() % get_height(b);
            clear_std();
            board_print(b, de);
            printf("Le dé à réalisé un %d\n", de+1);
            // Condition fail if the game continue
            if (!player_turn(b, player, true, de)) {
                goto endGame;
            }
        }
        for (int ia = 0; ia < nb_bot; ia += 1) {
            int de = rand() % get_height(b);
            clear_std();
            board_print_bot(b, &(bots[ia]), bot_turn(&(bots[ia]), b, de));
            if (nb_player > 0) {
                printf("Entrez qqch pour continuer\n");
                scan();
                if (buffer[0] == (int)'o' && (int)strlen(buffer) == 1 && (int)strlen(trash) == 0) {
                    if (print_option_ingame()) goto endGame;
                }
            }
        }
    }

    endGame:
    clear_std();
    print_center("Fin de la partie !!!");
    printf("\nVoici le classement :\n");
    print_ranking(b, nb_player + nb_bot);
    printf("\nEntrez qqch pour continuer\n");
    scan();
}


int main() {
    srand(time(NULL));

    bool running = true;

    // Initial variables, modifiable in the options
    int width_board = 9;
    int height_board = 6;
    int nb_hedgehog = 4;
    int prop_trap = 15;     // Proportion of trap
    int prop_wall = 10;     // Proportion of wall
    int nb_bot = 0;

    while (running)
    {
        clear_std();

        printf("Options ('%s')\n", MOVE_option);
        printf("\n\n\n");
        print_center("BIENVENUE sur le jeu Igel Ärgern");
        print_center("Le jeu de course de hérisson");
        printf("\nJouer (entrez le nombre de joueur [%d-%d])\n", 2-min(2, nb_bot), NB_PLAYER_MAX-nb_bot);
        printf("Tutoriel ('%s')\n", MOVE_tutorial);
        printf("Règles ('%s')\n", MOVE_rules);
        printf("Quitter ('q')\n");
        
        scan();

        int nb_player = string_to_ing(buffer);
        if (strcmp(buffer, MOVE_tutorial) == 0) {
            print_tutorial(width_board, height_board);
        }
        else if (strcmp(buffer, MOVE_rules) == 0) {
            print_rules();
        }
        else if (strcmp(buffer, MOVE_option) == 0) {
            print_option(&width_board, &height_board, &nb_hedgehog, &prop_trap, &prop_wall, &nb_bot);
        }
        else if (2-min(2, nb_bot) <= nb_player && nb_player <= NB_PLAYER_MAX-nb_bot) {
            play_game(width_board, height_board, nb_hedgehog, nb_player, nb_bot, prop_trap, prop_wall);
        }
        else {
            running = false;
        }
    }

    return 0;
}
