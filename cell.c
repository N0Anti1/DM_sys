#include "cell.h"

int cell_size = 24;

cell_t create_cell() {
  cell_t pile;
  pile.heap=tab[cell_size];
  pile.size=0;
  pile.is_trap=false;
  return(pile);
}


void pile_push(cell* p, char cnt){
  p->heap[p->size]=cnt;
  p->size++;
}

char pile_pop (cell* p){
  assert(p->size > 0);
  p->size--;
  char c = p->heap[p->size];
  return(c);
}

int pile_height(cell* p){
  return(p->size);
}

char pile_top(cell* p){
  assert(p->size > 0);
  char c = p->heap[p->size - 1];
  return(c);
}

char pile_peek(cell* p, int pos){
  assert(p->size > pos);
  char c = p->heap[p->size - pos - 1];
  return(c);
}