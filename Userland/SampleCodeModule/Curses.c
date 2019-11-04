#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include <stdint.h>
#include <stdbool.h>


void clearConsole()
{
    for (int row = 0; row < DISPLAY_ROW; row++)
    {
        for (int col = 0; col < DISPLAY_COL; col++)
        {
            printCharAt(' ',col,row);
        }

    }
}

int moveCursor(int row, int col)
{


    return OK;
}


int setColor( Color textColor, Color backgroundColor)
{


    return OK;
}


int printlnAt( char *str, int col, int row)
{
    int position = (row * DISPLAY_COL + col) * 2;

    writeAt(1,str,position);

    return OK;
}

int println( char *str)
{
    write(STDOUT,str);
    return OK;
}

int printCharAt( char ch, int col, int row)
{

    int position = (row * DISPLAY_COL + col) * 2;
    char temp[2]={ch,0};


    writeAt(STDOUT,temp,position);

    return OK;
}

int printChar( char ch)
{
    char buff[2]={0,0};
    buff[0]=ch;
    write(STDOUT,buff);

    return OK;
}


int readKey()
{
    
    static char buff[2];
    read(1,buff,2);
    return buff[0];
}