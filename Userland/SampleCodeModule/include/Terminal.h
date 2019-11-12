#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdarg.h>

void initializeTerminal();

void writeLineToTerminal(char * str);

int runTerminal();

void printf(char * format,...);

void putchar(char c);

void man();

int strcmp(char * s1,char * s2);

#endif