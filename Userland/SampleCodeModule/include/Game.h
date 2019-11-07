#ifndef GAME_H
#define GAME_H

#include <stdio.h>

int runGame(void);


int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel,int ball_direc,int lives);


void print_blocks(int[R_BLOCKS][C_BLOCKS] blocks);

#endif