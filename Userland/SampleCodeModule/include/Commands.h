#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdarg.h>

#include <stdint.h>

int printMem(uint64_t memDirection);

extern int infoReg();

int time();

int help();

int quotient();

int invalidOpcode();

int man();

void explainCommand(char * command);




#endif