#ifndef CONSOLE_DRIVER_API_H
#define CONSOLE_DRIVER_API_H

#include <stdarg.h>

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_);

void printLine( char * string);

void printChar(char ch);

void clearConsole();




#endif