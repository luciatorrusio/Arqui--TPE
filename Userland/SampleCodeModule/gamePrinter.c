#include "./include/gamePrinter.h"
#include "../Include/Syscalls.h"

void printOnScreen(int *pos,int lenght,int height,int color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_SQUARES,pos,lenght,height,color);
}
void print_border(int *pos,int lenght,int height,int color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_BORDER,pos,lenght,height,color);
}
void highlightTile(int *pos,int lenght,int height,int color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_HIGHLIGHT,pos,lenght,height,color);
}
void printPiece(int * pos, int piece, int color) {
   write(FD_PIECE, pos, piece, color, 0);
}