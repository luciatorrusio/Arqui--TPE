/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#include "include/Terminal.h"
#include "../Include/Curses.h"

#include <stdlib.h>
#include "../include/Debugger.h"



int main() {

	assertNotEqual(2,1);

	 initializeTerminal();

	 runTerminal();

	return 0xDEA;
}

