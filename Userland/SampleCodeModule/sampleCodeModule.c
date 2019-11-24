/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Game.h"
#include "include/gamePrinter.h"
#include <stdlib.h>
#include "../Include/Debugger.h"


int main() {


	printf("HI! Ask \"man\" for a command menu\n");
	
	 runTerminal();

	printf("LEAVING MAIN\n");

	return 0xDEA;
}

