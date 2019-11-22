/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#include "include/Terminal.h"
#include "../Include/Curses.h"

#include <stdlib.h>
#include "../Include/Debugger.h"



int main() {


	printf("STARTING MAIN\n");

	 runTerminal();

	printf("LEAVING MAIN\n");

	return 0xDEA;
}

