#include "../include/gamePrinter.h"
#include "../Include/Syscalls.h"

void printOnScreen(type type,int x,int y,int lenght,int height){
    switch(type){
        case BAR: {  
            printAt(x,y,lenght,height,0xFFFFFFFF);
            break;}
        case BALL: {  
            printAt(x,y,lenght,height,0xFFFFFFFF);
            break;}
        case BLOCK:{  
            printAt(x,y,lenght,height,0xFFFFFFFF);
            break;}       

    }
}
