#include <stdarg.h>
#include "include/Terminal.h"
#include "../Include/Curses.h"
#include "include/Commands.h"
#include "../Include/String.h"
#include <stdlib.h>

/***************************************************************/
/*                        Constantes                           */
/***************************************************************/

#define MAXBUFFER (600)

/***************************************************************/
/*                         Variables                           */
/***************************************************************/

static char TerminalType [MAXBUFFER];
static unsigned int TypeIndex = 0;

/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void clearArray(char * arr, int size);
void overwriteArray(char * src, char * dest);
void printTerminal();
int interpretCommand();
void overwriteArrayUpTo(char * src, char * dest,char c);

/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

int runTerminal(){

    clearArray(TerminalType,MAXBUFFER);
    TypeIndex = 0;
    do{
        
		int key = readKey();

		if(key >0){     
            if(key == 8 ){
                if(TypeIndex>0){
                    TerminalType[--TypeIndex] = 0;
                    RemoveLastCharFromDisplay();
                }

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

/***************************************************************/
/*                      Funciones Privadas                     */
/***************************************************************/

int interpretCommand(){
    char command[MAXBUFFER];
    char param1[MAXBUFFER];
    char param2[MAXBUFFER];

    overwriteArrayUpTo(TerminalType,command,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+1,param1,' ');
    overwriteArrayUpTo(TerminalType+strlen(command)+strlen(param1)+1,param2,' ');
    
    if(!strcmp(param2,"")){
        printfError("ERROR\n");
        return 0;
    }
    if(strcmp(command,"time") && strcmp(param1,""))
        time();
    else if(strcmp(command,"man") && strcmp(param1,""))
        man();
    else if(strcmp(command,"infoReg") && strcmp(param1,""))
        infoReg();
    else if(strcmp(command,"printMem") && !strcmp(param1,"")){
        int a = stringToInt(param1);
        printMem(a);
    }
    else if(strcmp(command,"game") && strcmp(param1,""))
        printf("aca iria el juego\n");
    else if(strcmp(command,"clear") && strcmp(param1,"")){ 
               clearConsole();
               }
    else
        printfError("%s%s%s: command not found \n",command,param1,param2);    
    
    return  0;
}
void man(){
    printf("time\nman\ngame\ninfoReg\nprintMem\ngame\nclear\n");
}


void printTerminal(){
    
    if(TerminalType[0])
        putChar(TerminalType[TypeIndex-1]);
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


