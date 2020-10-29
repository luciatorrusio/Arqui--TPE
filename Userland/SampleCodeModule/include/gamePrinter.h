#ifndef GAMEPRINTER_H
#define GAMEPRINTER_H

#include <stdarg.h>
#include <stdint.h>


void printOnScreen(int *pos,int lenght,int height,int fontColor);
void print_border(int *pos,int lenght,int height,int color);
void highlightTile(int *pos,int lenght,int height,int color);

#endif