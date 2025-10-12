#include "cell.h"


// J'ai changé la structure de cell_t pour une pile en tableau statique.
// Ainsi on n'est pas obligé d'initialiser la pile, puisqu'elle est vide de base.
cell_t create_cell() {
  cell_t c;
  c.size = 0;
  c.is_trap = false;
  return(c);
}

// J'ai accordé le nom de la fonction à celui du header.
void cell_push(cell_t* c, char ctn) {
  c->heap[c->size] = ctn;
  c->size++;
}

// On peut merge les deux dernières lignes avec :
// return c->heap[c->size];
char cell_pop(cell_t* c) {
  assert(c->size > 0);
  c->size--;
  char ch = c->heap[c->size];
  return(ch);
}

int cell_height(cell_t* c) {
  return(c->size);
}

// Idem que pour cell_pop
char cell_top(cell_t* c) {
  assert(c->size > 0);
  char ch = c->heap[c->size - 1];
  return(ch);
}

// Idem
char cell_peek(cell_t* c, int pos) {
  assert(c->size > pos);
  char ch = c->heap[c->size - pos - 1];
  return(ch);
}

// Il manquait
bool cell_is_trap(cell_t* c) {
    return c->is_trap;
}


void cell_print(cell_t* c, int slice, bool highlighted) {
    if (slice == 0) {
        if (cell_is_trap(c)) printf(" VVV ");
        else if (highlighted) printf(" === ");
        else printf(" --- ");
    }
    else if (slice == 1) {
        if (cell_is_trap(c)) printf(">");
        else printf("|");
        if (cell_height(c) > 0) {
            printf("%c%c%c", cell_top(c), cell_top(c), cell_top(c));
        }
        else {
            printf("   ");
        }
        if (cell_is_trap(c)) printf("<");
        else printf("|");
    }
    else if (slice == 2) {
        if (cell_is_trap(c)) printf(">");
        else printf("|");

        if (cell_height(c) == 0) {
            printf("   ");
        }
        else if (cell_height(c) == 1) {
            printf("%c%c%c", cell_top(c), cell_top(c), cell_top(c));
        }
        else if (cell_height(c) == 2) {
            // +32 to have lowercase
            printf("%c%c%c", cell_peek(c, 1)+32, cell_peek(c, 1)+32, cell_peek(c, 1)+32);
        }
        else if (cell_height(c) == 3) {
            printf("%c %c", cell_peek(c, 1)+32, cell_peek(c, 2)+32);
        }
        else if (cell_height(c) >= 4) {
            printf("%c%c%c", cell_peek(c, 1)+32, cell_peek(c, 2)+32, cell_peek(c, 3)+32);
        }

        if (cell_is_trap(c)) printf("<");
        else printf("|");
    }    
    else if (slice == 3) {
        if (cell_is_trap(c)) printf(" ^%c^ ", cell_height(c) <= 1 ? '^' : (char)48+cell_height(c));
        else {
            char c1 = '-', c2 = '-', c3 = '-';
            if (highlighted) {
                c1 = '=';
                c2 = '=';
                c3 = '=';
            }
            if (cell_height(c) >= 100) c1 = (char)(cell_height(c)/100+48);
            if (cell_height(c) >= 10) c3 = (char)(cell_height(c)%10+48);
            if (cell_height(c) >= 10) c2 = (char)((cell_height(c)%100)/10+48);
            else if (cell_height(c) > 0) c2 = (char)(cell_height(c)+48);
            printf(" %c%c%c ", c1, c2, c3);
        }
    }
    
}
