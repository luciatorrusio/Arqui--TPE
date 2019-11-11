
#include <stdarg.h>
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include <stdlib.h>
#include "../include/exception.h"




// Variables

#define MAXPBUFF 1000
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
int getHash(char * string);

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
                 printTypeLine();

            }else{ 

                TerminalType[TypeIndex++] = key;

                if(key == '\n'){

                    handleTerminalMovement();
                    interpretCommand();
                    clearArray(TerminalType,MAXBUFFER);
                    printTerminal();    
                }else{
                     printTypeLine();
                }
            }
        }
	}while(1);
}

int getHash(char * string){
    int hash=0;
    for(int i=0;*(string+i)!=0;i++){
        hash=hash*255+*(string+i);
    }
    return hash;
}

int interpretCommand(){
    char command[MAXBUFFER];
    overwriteArray(TerminalType,command);
    int com=getHash(command);
    if(com==getHash("time"))
        printf("La hora es %d",time());
    else if(com==getHash("man"))
        man();
    else if(com==getHash("infoReg"))
        infoReg();
    else if(com==getHash("printMem"))
        printMem(interpretCommand);
    //else if(com==getHash("game"))
      //  game();
    //else
     //   ERROR;    
    
    return  0;
}
void man(){
    printf("time man game infoReg printMem");
}


void handleTerminalMovement(){
    TypeIndex = 0;
    if(FirstAvailableLine == rows-3)
    {
        for( int i = 0 ; i < rows-3; i++)
           overwriteArray(TerminalDisplay[i+1],TerminalDisplay[i]);    
        FirstAvailableLine--;
    }

    overwriteArray(TerminalType,TerminalDisplay[FirstAvailableLine++]);
}


void printTerminal(){
    

    for(int i = 0 ; i < FirstAvailableLine; i ++){
        clearLine(i);
        printlnAt(TerminalDisplay[i],0,i);
    }

    clearLine(rows-2);
  // printTypeLine();
}

void printTypeLine(){
    int offset = 0;

    clearLine(rows-2);

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

void clearLine(int row){
    for(int i = 0 ; i < columns ; i++)
        printCharAt(' ',i,row);
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

void printf(char * format,...){
    char string[MAXPBUFF];
    for(int i=0;i<MAXPBUFF;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXPBUFF,format,args);
    va_end(args);
    writeLineToTerminal(string);
}
void putchar(char c){
	//ncPrintChar(c);
}