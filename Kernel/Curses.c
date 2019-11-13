#include "include/Curses.h"
#include "include/String.h"
#include <ConsoleDriver.h>

#define MAXBUFFER 500


void printf(const char * format,...){
    
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,format,args);
    va_end(args);

    printLine(string);

}

void printfColor(const char * format,int fontColor, int backgroundColor,...){
    
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,format,args);
    va_end(args);

    printLineColor(string,fontColor,backgroundColor);
}

void putChar(char ch){

    printChar(ch);

}
   





