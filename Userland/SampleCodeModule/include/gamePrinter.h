#ifndef GAMEPRINTER_H
#define GAMEPRINTER_H

#include <stdarg.h>
#include <stdint.h>

#define P_PAWN 0
#define P_BISHOP 1
#define P_ROOK 2
#define P_KNIGHT 3
#define P_KING 4
#define P_QUEEN 5

void printPiece(int * pos, int piece, int color);
void printOnScreen(int *pos,int lenght,int height,int fontColor);
void print_border(int *pos,int lenght,int height,int color);
void highlightTile(int *pos,int lenght,int height,int color);

#endif