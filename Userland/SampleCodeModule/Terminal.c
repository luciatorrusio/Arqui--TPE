
#include <stdarg.h>
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include <stdlib.h>




// Variables

#define MAXBUFFER (600)

static char TerminalType [MAXBUFFER];
static unsigned int TypeIndex = 0;
static unsigned int FirstAvailableLine = 0;



void clearArray(char * arr, int size);
void overwriteArray(char * src, char * dest);
void printTerminal();
int interpretCommand();
void overwriteArrayUpTo(char * src, char * dest,char c);
int strcmp(char * s1,char * s2);



int runTerminal(){
    do{
	
		int key = readKey();

		if(key >0){           
            if(key == 8 ){
                if(TypeIndex>0)
                    TerminalType[--TypeIndex] = 0;
                    printTerminal();

            }else{ 

                TerminalType[TypeIndex++] = key;
                printTerminal();

                if(key == '\n'){
                    interpretCommand();
                    clearArray(TerminalType,MAXBUFFER);
                    TypeIndex = 0;
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
        printf("ERROR\n");
        return 0;
    }
    if(strcmp(command,"time\n") && strcmp(param1,""))
        time();
    else if(strcmp(command,"man\n") && strcmp(param1,""))
        man();
    else if(strcmp(command,"infoReg\n") && strcmp(param1,""))
        infoReg();
    else if(strcmp(command,"printMem\n") && !strcmp(param1,"")){
        printMem(param1);
    }
    else if(strcmp(command,"game\n") && strcmp(param1,""))
        printf("aca iria el juego\n");
    else if(strcmp(command,"clear\n") && strcmp(param1,""))
        printf("aca iria el clear\n");
    else
       printf("ERROR\n");    
    
    return  0;
}
void man(){
    printf("time man game infoReg printMem\n");
}





void printTerminal(){
    
    if(TerminalType[0])
        printf(TerminalType + strlen(TerminalType)-1);
}



void clearArray(char * arr, int size){

    for (int i = 0; i < size; i++)
        arr[i] = 0;
}


void overwriteArray(char * src, char * dest){
    overwriteArrayUpTo(src,dest,0);
}

void overwriteArrayUpTo(char * src, char * dest,char c){
    clearArray(dest,MAXBUFFER);
    int i;
    for (i = 0; src[i]!=0 && src[i]!='\n' && i < MAXBUFFER && src[i]!=c; i++)
        dest[i] = src[i];
    if(i!=MAXBUFFER){
        dest[i]=0;
    }
}


int strcmp(char * s1,char * s2){
    int i;
    for(i=0;*(s1+i)!=0 && *(s2+i)!=0 && *(s1+i)==*(s2+i);i++);

    if(*(s1+i)==0 && *(s2+i)==0)
     return 1;
    return 0; 
}