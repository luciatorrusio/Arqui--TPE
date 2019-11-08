#include "./include/gamePrinter.h"
#include "../Include/Syscalls.h"

void printOnScreen(type type,int x,int y,int lenght,int height,int color){
    switch(type){
        case BAR: {  
            printAt(x,y,lenght,height,color);
            break;}
        case BALL: {  
            printAt(x,y,lenght,height,color);
            break;}
        case BLOCK:{  
            printAt(x,y,lenght,height,color);
            break;}       

    }
}
