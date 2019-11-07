/* sampleCodeModule.c */
#include "../include/Time.h"
#include "../include/String.h"
#include "../include/Syscalls.h"

#include "include/Terminal.h"
#include "../include/Curses.h"

#include <stdlib.h>



int main() {

	initializeTerminal();

	runTerminal();

	return 0xDEA;
}

