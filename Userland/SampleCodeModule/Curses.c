#include "./include/Curses.h"
#include "./include/String.h"
#include "./include/Syscalls.h"
#include "./include/deviceInfo.h"
#include "./include/stdint.h"
#include <stdbool.h>

typedef struct{
    char ch;
    int fontColor;
    int backgroundColor;
    int x;
    int y;
}ColorChar;


#define MAXBUFFER 1000




void clearConsole()
{
    delete(FD_STDOUT,(void*)DELETE_ALL_DISPLAY,NULL,NULL,NULL);
}


void printf(const char * format, ...){
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,(char*)format,args);
    va_end(args);

    write(FD_STDOUT,(void*)string,0,0,0);
}

void printfColorAt(const char * format,int fontColor, int backgroundColor,int x,int y,...){
    unsigned int charWidth;
    getCharWidth(&charWidth);
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,(char*)format,args);
    va_end(args);

    ColorChar colorString[strlen(string)];
    int i;
    int posX=x;
    int posY=y;
    for(i = 0; string[i]!=0;i++,posX+=charWidth){
        colorString[i].ch = string[i];
        colorString[i].fontColor = fontColor;
        colorString[i].backgroundColor = backgroundColor;
        colorString[i].x=posX;
        colorString[i].y=posY;

    }
        colorString[i].ch = 0;

        write(FD_STDOUT_COLOR,(void*)colorString,0,0,0);

}


void printfError(const char * format,...){
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,(char*)format,args);
    va_end(args);

    write(FD_STDERR,(void*)string,0,0,0);

}



void RemoveLastCharFromDisplay(){
    delete(FD_STDOUT,(void*)DELETE_CURRENT_CHAR,NULL,NULL,NULL);
}


void putChar( char ch)
{
    char buff[2]={0,0};
    buff[0]=ch;
    write(FD_STDOUT,(void*)buff,0,0,0);

}


int readKey()
{
    static char buff[2];
    read(FD_STDIN,buff,(void*)2,0,0);
    char retValue = buff[0];
    buff[0] = 0;
    return retValue;
}
