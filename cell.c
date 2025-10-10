#include <stdio.h>


typedef struct cell {
    int i;
} cell_t;

void init_cell(cell_t* c) {
    c->i = 2;
}

cell_t def_cell() {
    cell_t c;
    c.i = 1;
    return c;
}


int main() {

    cell_t cell;
    init_cell(&cell);
    cell_t cell2 = def_cell();

    printf("%d\n", cell.i);
    printf("%d\n", cell2.i);

}
