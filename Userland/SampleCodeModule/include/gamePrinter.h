#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
typedef enum type{BAR,BALL,BLOCK,NONE} type; 

void printOnScreen(type type,int x,int y,int lenght,int height,int fontColor);