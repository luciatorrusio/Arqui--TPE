#include "include/Curses.h"
#include "include/String.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


char * display = (char *)0xB8000;

static unsigned int position = 0;
static Color FntColor = Blue;
static Color BgColor = LightGreen;

int processKeyboardInput(int input);

int formatColor(Color text, Color background)
{

    return (int)text + 0x10 * (int)background;
}

void clearConsole()
{

    for (int i = 0; i < DISPLAY_COL * DISPLAY_ROW * 2; i+=2)
    {
            printCharAt( ' ', i);
    }
    

}

int moveCursor(int row, int col)
{


    return OK;
}


int setColor( Color textColor, Color backgroundColor)
{
    if (textColor > 0xF || textColor < 0)
        return ERROR;

    if (backgroundColor > 0xF || backgroundColor < 0)
        return ERROR;

    FntColor = textColor;
    BgColor = backgroundColor;

    return OK;
}



int printlnAt(char *str, unsigned int pos)
{
    if (pos > DISPLAY_COL * DISPLAY_ROW *2)
        return ERROR;

 
    if (str == NULL)
        return ERROR;

    for (int i = 0 ; str[i]!=0; i++){

        if(str[i]!= '\n'){
            printCharAt(str[i],pos);
            pos += 2;
        }else{
            int tempCol = 0;
            int tempRow = (pos/2) / DISPLAY_COL;
            tempRow++;
            pos = 2 * (DISPLAY_COL * tempRow + tempCol);
        }
    }
    return OK;
}

int println(char *str)
{
    for (int i = 0; str[i] != 0; i++)
    {
        printChar(str[i]);

    }

    return OK;
}

void getColor(Color * textColor, Color * backgroundColor){
    *textColor = FntColor;
    *backgroundColor = BgColor;
}

int printCharAt(char ch, unsigned int position){
    display[position] = ch;
    display[position + 1] = formatColor(FntColor, BgColor);

    return OK;
}

int printChar( char ch)
{

    if(ch != '\n'){
        printCharAt(ch,position);        
        position += 2;
    }else{
        int tempCol = 0;
        int tempRow = (position/2) / DISPLAY_COL;
        tempRow++;
        position = 2 * (DISPLAY_COL * tempRow + tempCol);
    }
    return OK;
}
