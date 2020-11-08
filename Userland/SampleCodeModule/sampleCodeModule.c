/* sampleCodeModule.c */
#include "./include/Time.h"
#include "./include/String.h"
#include "./include/Syscalls.h"

#include "include/Terminal.h"
#include "./include/Curses.h"
#include "include/Game.h"
#include "include/gamePrinter.h"
#include <stdlib.h>
#include "./include/deviceInfo.h"
void menu(){
	unsigned int init;
	unsigned int aux;
	unsigned int charHeight;
	getCharHeight(&charHeight);
	getBpp(&init);
	setSize(5*init);
	getBpp(&aux);

	printf("BBP: %d",init);
	
	int position=67;
	int y=30;
	printfColorAt("TPE ARQUI",0xFF44FF,0x00,position,y);
    setSize(init*2);
	getBpp(&aux);
    y+=charHeight*aux+3;
    printfColorAt("Ponce 59220, Torrusio 59489, Diaz Kralj 60495",0xFFFFFF,0x00,position,y);
    y+=charHeight*aux+3;
    printfColorAt("1) Game",0xFFFFFF,0x00,position*2,y);
    printfColorAt("2) Terminal",0xFFFFFF,0x00,position*4+30,y);
	y+=charHeight+20;
	printfColorAt("3) Exit",0xFFFFFF,0x00,position*3+20,y);
    setSize(init);

}

static int selector = -1;

int main() {

	int exit=0;
	while(exit!=1)
	{
		
		if(selector == -1){
			clearConsole();
			menu();
			while(((selector=readKey())!='1') && (selector!='2') && (selector!='3'));
			clearConsole();
			if(selector == '2')
				printf("HI! Ask \"man\" for a command menu\n");
		}

		if(selector == '2'){

			
			switch(runTerminal()){
				case 1: exit = 1; break;
				case 2: selector = '1'; break;
			}
		}
		else if(selector == '1'){
			clearConsole();
			switch(runGame()){
				case 1: exit = 1; break;
				default: selector = '2'; break;
			}
			clearConsole();
			if(selector == '2')
				printf("HI! Ask \"man\" for a command menu\n");

		}
		else{
			exit = 1;
		}


		
	}

	clearConsole();

	unsigned int init;
	getBpp(&init);
	setSize(6*init);
	
	int position=70;
	int y=50;
	printfColorAt("BYE!",0xFF44FF,0x00,position,y);
	return 0xDEA;
}

