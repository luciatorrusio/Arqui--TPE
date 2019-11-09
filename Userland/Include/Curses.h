#ifndef CURSES
#define CURSES


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






void initializeCurses();
void getConsoleDimensions(int * cols, int * rows);
// Use only to interface directly with the kernel API.
// DO NOT USE IT WHILE RUNNING THE TERMINAL. 
// If you are creating a terminal command, please use the one provided in terminal.h

void clearConsole();

int moveCursor(int row, int col);

int setColor(Color textColor, Color backgroundColor);

int setTextColor( Color textColor);

int setBackgroundColor(int backgoundColor);

int printlnAt(char * str, int col, int row);

int println( char * str);

int printCharAt( char ch,int col, int row);

int printChar( char ch);

int readKey();

#endif


