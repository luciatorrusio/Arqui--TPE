#ifndef STRINGH
#define STRINGH
#include <stdarg.h>

#include <stdint.h>


int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

void HexToString(char * buff, int buffSize, uint64_t num);

void preppend(char * src, char * dest, unsigned size);

void append(char * src, char * dest, unsigned size);

void snprintf(char * string, int size, char * format, va_list args);

void handleFormat(char type,int * k,char * string,int size,va_list args);





#endif