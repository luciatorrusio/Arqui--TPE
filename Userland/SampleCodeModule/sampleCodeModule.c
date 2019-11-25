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
#include "../Include/deviceInfo.h"
void menu(){
	unsigned int init;
	unsigned int aux;
	unsigned int charHeight;
	getCharHeight(&charHeight);
	getBpp(&init);
	setSize(5*init);
	getBpp(&aux);
	
	int position=67;
	int y=30;
	printfColorAt("TPE DE PC",0xFF44FF,0x00,position,y);
    setSize(init*2);
	getBpp(&aux);
    y+=charHeight*aux+3;
    printfColorAt("11111,Dellisola   59123,Torrusio   59820,PUIG",0xFFFFFF,0x00,position,y);
    y+=charHeight*aux+3;
    printfColorAt("1) Game",0xFFFFFF,0x00,position*2,y);
    printfColorAt("2) Terminal",0xFFFFFF,0x00,position*4+30,y);
	y+=charHeight+20;
	printfColorAt("3) Exit",0xFFFFFF,0x00,position*3+20,y);
    setSize(init);

}

static int selector = -1;

int main() {
	runGame();
	return 0xDEA;
}

