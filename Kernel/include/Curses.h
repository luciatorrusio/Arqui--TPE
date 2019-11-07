#ifndef CURSES_API_H
#define CURSES_API_H

#include <stdint.h>


#define ERROR -1
#define OK 0

typedef enum {
    Black= 0x000000,
    Blue = 0x1,
    Green = 0x2,
    Aqua = 0x3,
    Red = 0x4,
    Purple = 0x5,
    Yellow = 0x6,
    White = 0xFFFFFF,
    Gray = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xA,
    LightAqua = 0xB,
    LightRed = 0xC,
    LightPurple = 0xD,
    LightYellow = 0xE,
    LightWhite = 0xF
}Color;




void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_);

void clearConsole();

int moveCursor(int row, int col);

int setColor(Color textColor, Color backgroundColor);

int printlnAt(char *str, unsigned int position);

int printChar( char ch);

int printCharAt(char ch, uint64_t x, uint64_t y);

int println(char * str);

void getColor(Color * textColor, Color * backgroundColor);

void getScreenDimensions(int * cols, int * rows);




#endif


