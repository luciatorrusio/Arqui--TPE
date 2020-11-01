#ifndef DEBUGGER_API_H
#define DEBUGGER_API_H
#include <stdbool.h>
#include "stdint.h"
#include "deviceInfo.h"
#include "Curses.h"
#include "keyboard.h"
#include "ConsoleDriver.h"
#include "String.h"

void ThrowCustomException(char * str);

void PrintExceptionDetails(char * name,uint64_t * stackPointer,uint64_t* instructionPointer);

bool assertEqual(void * val1, void * val2);

bool assertNotEqual(void * val1, void * val2);

#endif