
#include <stdarg.h>
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
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
void overwriteArrayUpTo(char * src, char * dest,char c);
int strcmp(char * s1,char * s2);
void initializeTerminal(){
    initializeCurses();
    getConsoleDimensions(&columns,&rows);  
}

int runTerminal(){

    clearConsole();
	time();
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

int interpretCommand(){
    char command[MAXBUFFER];
    char param1[MAXBUFFER];
    char param2[MAXBUFFER];

    overwriteArrayUpTo(TerminalType,command,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+1,param1,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+strlen(param1)+1,param2,' ');
    
    if(!strcmp(param2,"")){
        printf("ERROR");
        return 0;
    }
    if(strcmp(command,"time") && strcmp(param1,""))
        time();
    else if(strcmp(command,"man") && strcmp(param1,""))
        man();
    else if(strcmp(command,"infoReg") && strcmp(param1,""))
        infoReg();
    else if(strcmp(command,"printMem") && !strcmp(param1,"")){
        printMem(param1);
    }
    else if(strcmp(command,"game") && strcmp(param1,""))
        printf("aca iria el juego");
    else if(strcmp(command,"clear") && strcmp(param1,""))
        printf("aca iria el clear");
    else
       printf("ERROR");    
    
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
    overwriteArrayUpTo(src,dest,0);
}

void overwriteArrayUpTo(char * src, char * dest,char c){
    clearArray(dest,columns + 1);
    int i;
    for (i = 0; src[i]!=0 && src[i]!='\n' && i < MAXBUFFER && src[i]!=c; i++)
        dest[i] = src[i];
    if(i!=MAXBUFFER){
        dest[i]=0;
    }
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
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,format,args);
    va_end(args);
    writeLineToTerminal(string);
}
char getchar(){
	char c=readKey();
    return c;
}
int strcmp(char * s1,char * s2){
    int i;
    for(i=0;*(s1+i)!=0 && *(s2+i)!=0 && *(s1+i)==*(s2+i);i++);

    if(*(s1+i)==0 && *(s2+i)==0)
     return 1;
    return 0; 
}