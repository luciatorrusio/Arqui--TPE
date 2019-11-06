#ifndef CURSES_API_H
#define CURSES_API_H

#define DISPLAY_COL 80
#define DISPLAY_ROW 25
#define ERROR -1
#define OK 0

typedef enum {
    Black= 0x0,
    Blue = 0x1,
    Green = 0x2,
    Aqua = 0x3,
    Red = 0x4,
    Purple = 0x5,
    Yellow = 0x6,
    White = 0x7,
    Gray = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xA,
    LightAqua = 0xB,
    LightRed = 0xC,
    LightPurple = 0xD,
    LightYellow = 0xE,
    LightWhite = 0xF
}Color;






void clearConsole();

int moveCursor(int row, int col);

int setColor(Color textColor, Color backgroundColor);

int printlnAt(char *str, unsigned int position);

int printChar( char ch);

int printCharAt(char ch, unsigned int position);

int println(char * str);

void getColor(Color * textColor, Color * backgroundColor);




#endif


