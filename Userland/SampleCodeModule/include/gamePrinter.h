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

void printPiece(int * pos, uint64_t piece, uint64_t color);
void printOnScreen(int * pos, uint64_t lenght, uint64_t height, uint64_t color);
void print_border(int * pos, uint64_t lenght, uint64_t height, uint64_t color);
void highlightTile(int * pos,  uint64_t lenght, uint64_t height, uint64_t color);

#endif