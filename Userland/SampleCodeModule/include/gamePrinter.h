#ifndef GAMEPRINTER_H
#define GAMEPRINTER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
typedef enum type{BAR,BALL,BLOCK} type; 

void printOnScreen(type type,int x,int y,int lenght,int height,int fontColor);
#endif