#include "./include/gamePrinter.h"
#include "../Include/Syscalls.h"

void printOnScreen(int *pos,int lenght,int height,int color){
   
   write(5,pos,lenght,height,color);

   //printAt(pos,lenght,height,color);

}

