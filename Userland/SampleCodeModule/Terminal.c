
#include "include/Terminal.h"
#include "../include/Curses.h"
#include "include/Commands.h"
#include <stdlib.h>




// Variables

#define MAXBUFFER (600)

static char TerminalDisplay [60][MAXBUFFER];
static char TerminalType [MAXBUFFER];
static unsigned int TypeIndex = 0;
static unsigned int FirstAvailableLine = 0;

static int columns;
static int rows;

void clearArray(char * arr, int size);
void overwriteArray(char * src, char * dest);
void handleTerminalMovement();
void printTerminal();
int interpretCommand();
void printTypeLine();

void initializeTerminal(){
    initializeCurses();

    getConsoleDimensions(&columns,&rows);
}

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
                    printTerminal();
    
                }
            }
                            printTypeLine();

            
            

        }

	}while(1);
}


int interpretCommand(){
    char command[MAXBUFFER];
    overwriteArray(TerminalType,command);

    
    return  0;
    

}

void handleTerminalMovement(){
    TypeIndex = 0;
    if(FirstAvailableLine == columns-2)
    {
        for( int i = 0 ; i < rows-3; i++)
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

   printTypeLine();
}

void printTypeLine(){
    int offset = 0;

    if (TypeIndex > columns)
    {
        offset = TypeIndex - columns;
    }

    printlnAt(TerminalType + offset,0,rows-2);

}

void clearArray(char * arr, int size){

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void overwriteArray(char * src, char * dest){

    clearArray(dest,columns + 1);
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