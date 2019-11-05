
#include "include/Terminal.h"
#include "../Include/Curses.h"

#include <stdlib.h>



// Variables

static char TerminalDisplay [DISPLAY_ROW-1][DISPLAY_COL+1];
static char TerminalType [DISPLAY_COL+1];
static unsigned int TypeIndex = 0;
static unsigned int FirstAvailableLine = 0;

void clearArray(char * arr, int size);
void overwriteArray(char * src, char * dest);
void handleTerminalMovement();
void printTerminal();
int interpretCommand();


int runTerminal(){

    clearConsole();
	do{
		
		int key = readKey();
		if(key >0){

            TerminalType[TypeIndex++] = key;

            if(key == '\n'){
                interpretCommand();

                handleTerminalMovement();

                printTerminal();
		    }
        }

	}while(1);
}


int interpretCommand(){
    char command[DISPLAY_COL+1];
    overwriteArray(TerminalType,command);

    // Interpretar el comando

    // Devuelve un valor de retorno
    return 0;

}

void handleTerminalMovement(){
    TypeIndex = 0;
    if(FirstAvailableLine == DISPLAY_ROW-2)
    {
        for( int i = 0 ; i < DISPLAY_ROW-3; i++)
           overwriteArray(TerminalDisplay[i+1],TerminalDisplay[i]);    
        FirstAvailableLine--;
    }

    overwriteArray(TerminalType,TerminalDisplay[FirstAvailableLine++]);
    clearArray(TerminalType,DISPLAY_COL + 1);
}


void printTerminal(){
    
    clearConsole();

    for(int i = 0 ; i < FirstAvailableLine; i ++)
        printlnAt(TerminalDisplay[i],0,i);

    printlnAt(TerminalType,0,DISPLAY_ROW-1);
}

void clearArray(char * arr, int size){

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void overwriteArray(char * src, char * dest){

    clearArray(dest,DISPLAY_COL + 1);
    for (int i = 0; src[i]!=0; i++)
        dest[i] = src[i];
    
}