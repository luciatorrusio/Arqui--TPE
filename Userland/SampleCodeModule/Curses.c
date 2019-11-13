#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include <stdint.h>
#include <stdbool.h>


#define MAXBUFFER 200



void clearConsole()
{
 
}


void printf(const char * format, ...){
    char string[MAXBUFFER];
    for(int i=0;i<MAXBUFFER;i++)
        *(string+i)=0;
    va_list args;
	va_start(args,format);
    snprintf(string,MAXBUFFER,format,args);
    va_end(args);

    write(STDOUT,string);
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