#ifndef STRINGH
#define STRINGH

#include <stdint.h>


int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

void HexToString(char * buff, int buffSize, uint64_t num);

void preppend(char * src, char * dest, unsigned size);

void append(char * src, char * dest, unsigned size);




#endif