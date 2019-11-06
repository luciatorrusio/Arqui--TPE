#include "include/Curses.h"
#include "include/String.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <VideoDriver.h>


static uint64_t pos_x = 0;
static uint64_t pos_y = 0;



static Color FntColor = White;
static Color BgColor = Black;

static int charHeight;
static int charWidth;
static int screenHeight;
static int screenWidth;



void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_){
    charHeight = charHeight_;
    charWidth = charWidth_;
    screenHeight = screenHeight_;
    screenWidth = screenWidth_;
}


void nextColumn(){

    pos_x+= charWidth;

}
void nextRow(){
    pos_x = 0;
    pos_y += charHeight;
}


void clearConsole()
{
    pos_x = 0;
    pos_y = 0; 

    while(pos_y < screenHeight){
        while(pos_x < screenWidth){
            
            printCharAt(' ',pos_x,pos_y);
            nextColumn();
        }
        nextRow();
    }

    pos_x = 0;
    pos_y = 0;    

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
    // if (pos > DISPLAY_COL * DISPLAY_ROW *2)
    //     return ERROR;

 
    // if (str == NULL)
    //     return ERROR;

    // for (int i = 0 ; str[i]!=0; i++){

    //     if(str[i]!= '\n'){
    //        // printCharAt(str[i],pos);
    //         pos += 2;
    //     }else{
    //         int tempCol = 0;
    //         int tempRow = (pos/2) / DISPLAY_COL;
    //         tempRow++;
    //         pos = 2 * (DISPLAY_COL * tempRow + tempCol);
    //     }
    // }
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

int printCharAt(char ch, uint64_t x, uint64_t y){

    drawChar(x,y,ch,FntColor,BgColor);


    return OK;
}

int printChar( char ch)
{

    if(ch != '\n'){
        if(pos_x >= screenWidth)
            nextRow();
        printCharAt(ch,pos_x,pos_y);    
        nextColumn();    
    }else{
        nextRow();
    }
    return OK;
}
