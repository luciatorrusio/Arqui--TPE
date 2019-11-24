#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdbool.h>

extern void ThrowCustomException(char * str);

bool assertEqual(void * val1, void * val2);

bool assertNotEqual(void * val1, void * val2);


#endif