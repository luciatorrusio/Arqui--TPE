#include "./include/gamePrinter.h"
#include "./include/Syscalls.h"

void printOnScreen(int *pos, uint64_t lenght, uint64_t height, uint64_t color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_SQUARES,pos,(void *)lenght,(void *)height,(void *)color);
}
void print_border(int *pos, uint64_t lenght, uint64_t height, uint64_t color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_BORDER,pos,(void *)lenght,(void *)height,(void *)color);
}
void highlightTile(int *pos, uint64_t lenght, uint64_t height, uint64_t color){

				//  printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",5,pos[0],pos[1],lenght,height,color);

   write(FD_HIGHLIGHT,pos,(void *)lenght,(void *)height,(void *)color);
}
void printPiece(int * pos, uint64_t piece, uint64_t color) {
   write(FD_PIECE, pos, (void *) piece, (void *) color, 0);
}