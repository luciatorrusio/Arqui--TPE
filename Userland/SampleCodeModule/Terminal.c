
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include <stdlib.h>




// Variables

#define MAXBUFFER (DISPLAY_COL * 5)

static char TerminalDisplay [DISPLAY_ROW-1][MAXBUFFER];
static char TerminalType [MAXBUFFER];
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
            if(key == 8 ){
                if(TypeIndex>0)
                    TerminalType[--TypeIndex] = 0;

            }else{ 

                TerminalType[TypeIndex++] = key;

                if(key == '\n'){

                    handleTerminalMovement();
                    interpretCommand();
                    clearArray(TerminalType,MAXBUFFER);
                    //printTerminal();
    
                }
            }
            
            printTerminal();

        }

	}while(1);
}


int interpretCommand(){
    char command[MAXBUFFER];
    overwriteArray(TerminalType,command);


    return printMem(0);

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
}


void printTerminal(){
    
    clearConsole();

    for(int i = 0 ; i < FirstAvailableLine; i ++)
        printlnAt(TerminalDisplay[i],0,i);

    int offset = 0;

    if (TypeIndex > DISPLAY_COL)
    {
        offset = TypeIndex - DISPLAY_COL;
    }
    

    printlnAt(TerminalType + offset,0,DISPLAY_ROW-1);
}

void clearArray(char * arr, int size){

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void overwriteArray(char * src, char * dest){

    clearArray(dest,DISPLAY_COL + 1);
    for (int i = 0; src[i]!=0 && i < MAXBUFFER; i++)
        dest[i] = src[i];
    
}


void writeLineToTerminal(char * str){
    char temp[MAXBUFFER];
    overwriteArray(TerminalType,temp);

    overwriteArray(str,TerminalType);



    handleTerminalMovement();
    printTerminal();

    overwriteArray(temp,TerminalType);
    
    
    }