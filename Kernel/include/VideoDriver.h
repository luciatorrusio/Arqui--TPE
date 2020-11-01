#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

static unsigned int SCREEN_WIDTH = 1024;
static unsigned int SCREEN_HEIGHT = 768;

#include "pieces.h"

void startVideoDriver();

void drawChar(int x, int y, char character, int fontColor, int background);

void setSize(unsigned int s);

void getBpp(int * size);

void setSize(unsigned int size);

void print(int *pos,int lenght,int height,int fontColor);

void print_border(int *pos,int lenght,int height,int fontColor);

void print_highlight(int *pos,int lenght,int height,int fontColor);

void print_piece(int * pos, int piece, int fontColor);

#endif