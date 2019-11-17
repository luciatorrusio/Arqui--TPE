#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include <stdint.h>
#include <stdbool.h>


#define MAXBUFFER 1000
#define FD_LAST_CHAR 1
#define FD_ALL_DISPLAY 2



void clearConsole()
{
    delete(FD_ALL_DISPLAY);
}


void printf(const char * format, ...){
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,(char*)format,args);
    va_end(args);

    write(STDOUT,string);
}

void printfError(const char * format,...){
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,(char*)format,args);
    va_end(args);

    write(STDERR,string);

}



void RemoveLastCharFromDisplay(){
    delete(FD_LAST_CHAR);
}


void putChar( char ch)
{
    char buff[2]={0,0};
    buff[0]=ch;
    write(STDOUT,buff);

}


int readKey()
{
    static char buff[2];
    read(1,buff,2);
    char retValue = buff[0];
    buff[0] = 0;
    return retValue;
}