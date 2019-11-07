#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include <stdint.h>
#include <stdbool.h>

static int displayRows;
static int displayCols;

typedef struct 
{
    int columns;
    int rows;

}VideoConfiguration;


void initializeCurses(){
    VideoConfiguration config;

    read(2,(void *)&config,0);
    displayRows = config.rows;
    displayCols = config.columns;


    
}

void getConsoleDimensions(int * cols, int * rows){
    *cols = displayCols;
    *rows = displayRows;
}

int calculatePosition(int col, int row){

    return col + row * displayCols;
}


void clearConsole()
{
    for (int row = 0; row < displayRows; row++)
    {
        for (int col = 0; col < displayCols; col++)
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
    int position = calculatePosition(col,row);

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

    int position = calculatePosition(col,row);
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
    char retValue = buff[0];
    buff[0] = 0;
    return retValue;
}