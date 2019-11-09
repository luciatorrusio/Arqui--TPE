#include "./include/gamePrinter.h"
#include "../include/Syscalls.h"

void printOnScreen(int x,int y,int lenght,int height,int color){
   
   

   printAt(x,y,lenght,height,color);

}

void screenSizes(int * lenght,int * height){
   getScreenSizes(lenght,height);
}

