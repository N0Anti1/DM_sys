#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/ioctl.h>


#ifndef DATA_H
#define DATA_H


#define NB_PLAYER_MAX 26
#define NB_HEDGEHOG_MAX 300
#define WIDTH_MAX 26
#define HEIGHT_MAX 9

// The movements are defined with the zqsd keys
#define MOVE_up 'z'
#define MOVE_down 's'
#define MOVE_right 'd'

#define MOVE_tutorial "t"
#define MOVE_rules "r"
#define MOVE_option "o"


#endif
