#ifndef STRING_API_H
#define STRING_API_H
#include <stdint.h>

int strlen(char * str);

void IntToString(char * buff, int buffSize, uint64_t num);

void HexToString(char * buff, int buffSize, uint64_t num);




#endif