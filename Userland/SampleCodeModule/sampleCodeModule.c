/* sampleCodeModule.c */
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Game.h"
#include "include/gamePrinter.h"
#include <stdlib.h>
#include "include/Speaker.h"


int main() {
	beep();

// 	initializeTerminal();

// 	//printf("tick %d\n",getTicks());

// 	uint64_t baseTicks = 0,realTicks = 0, gameTicks = 0, previusTick = 0;
	

//     baseTicks = getTicks();
//     do{
//         realTicks = getTicks() - baseTicks ;

//         if(realTicks % 15 == 0 && realTicks !=previusTick){
//             gameTicks++;
// 			previusTick = realTicks;
// // printf("tick %d\n",getTicks());
//             printf("GameTick: %d\n",gameTicks);
//         }


//     }while(1);


	runGame();

	return 0xDEA;
}

