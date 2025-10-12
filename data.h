#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <sys/ioctl.h>



#define NB_HEDGEHOG 2
#define NB_PLAYER_MAX 26
const int WIDTH = 3;
const int HEIGHT = 3;

const char MOVE_up = 'u';
const char MOVE_down = 'b';
const char MOVE_right = 'd';
const char* MOVE_tutorial = "t";
const char* MOVE_rules = "r";
const char* MOVE_option = "o";
