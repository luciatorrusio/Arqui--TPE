#ifndef DEBUGGER_API_H
#define DEBUGGER_API_H
#include <stdbool.h>

void ThrowCustomException(char * str);

void PrintExceptionDetails(char * name);

bool assertEqual(void * val1, void * val2);

bool assertNotEqual(void * val1, void * val2);

#endif