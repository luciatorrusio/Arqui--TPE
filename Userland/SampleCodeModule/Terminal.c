
#include "include/Terminal.h"
#include "../Include/Curses.h"



// Variables

static char TerminalDisplay [DISPLAY_COL * (DISPLAY_ROW-1)];
static char TerminalType [DISPLAY_COL+1];



int runTerminal(){

	do{
		
		int key = readKey();

		if(key != -1){
			
			printChar(key);
			
		}

	}while(1);

}