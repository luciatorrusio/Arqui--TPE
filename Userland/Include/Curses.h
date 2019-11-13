#ifndef CURSES
#define CURSES

#include <stdarg.h>







void clearConsole();


void printf(const char * format, ...);

void printfError(const char * format,...);

void putChar(char ch);






int readKey();

#endif


