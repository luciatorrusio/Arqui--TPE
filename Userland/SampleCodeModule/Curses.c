#include "../Include/Curses.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

extern int __ReadKey__();


int processKeyboardInput(int input);



void clearConsole()
{
    for (int i = 0; i < DISPLAY_ROW; i++)
    {
        for (int j = 0; j < DISPLAY_COL; j++)
        {
            printCharAt( ' ', j, i);
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

    writeAt(1," ",position);

    

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
    return processKeyboardInput(__ReadKey__());
}

enum Commands
{
    Escape = -1,
    Control = -2,
    LShift = -3,
    Rshift = -4,
    PrintScreen = -5,
    Alt = -6,
    CapsLock = -7,
    NumLock = -8,
    ScrollLock = -9,
    Home = -10,
    ArrowUp = -11,
    ArrowDown = -12,
    ArrowLeft = -13,
    ArrowRight = -14,
    End = -15,
    PageUp = -16,
    Delete = -17

};

#define F(x) (CapsLock - x)

static const int KeyMap[] = {
    //1
    Escape, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
    //16
    9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 13, Control,
    //32
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', LShift, '\\',
    //46
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', Rshift, PrintScreen, CapsLock,
    //59
    ' ', CapsLock, F(1), F(2), F(3), F(4), F(5), F(6), F(7), F(8), F(9), F(10),
    //71
    NumLock, ScrollLock, Home, ArrowUp, PageUp, 0, 0, 0, 0, 0, 0, 0, 0, 0, Delete,
    //86
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, F(11), F(12), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const int ShiftKeyMap[] = {
    //0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //32
    ' ', '!', '\"', '#', '&', '%', '\"', '(', ')', '*', '+', '<', '_', '>', '?', ')',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ':', ':', '<', '+', '>', '?',
    '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '^', '_', '~', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{',
    '|', '}', '~', 0};

static bool Mayusc = false;
static bool Shift = false;

void handleBreaks(int input);
int handleASCII(int PressedKey);
void handleCommands(int PressedKey);

int processKeyboardInput(int input)
{
    // if (Mayusc)
    // {
    //     printlnAt(NULL, "CAPS ON ", 0, 10);
    // }
    // else
    // {
    //     printlnAt(NULL, "CAPS OFF", 0, 10);
    // }

    handleBreaks(input);

    if (input <= 0 || input > 86)
        return -1;

    char arr[20];
    HexToString(arr, 20, input);
    // printlnAt(NULL, "Codigo:       ", 0, 0);
    // printlnAt(NULL, arr, 10, 0);

    int PressedKey = KeyMap[input];

    // printlnAt(NULL, "valor real:            ", 18, 0);
    IntToString(arr, 20, PressedKey + (Mayusc ? 'A' - 'a' : 0));
    // printlnAt(NULL, arr, 30, 0);

    if (PressedKey > 0)
    {
        int asciiValue = handleASCII(PressedKey);
        if (asciiValue != -1)
            return asciiValue;
    }

    handleCommands(PressedKey);

    return -1;
}

void handleBreaks(int input)
{
    input = input - 0x80;

    if (input > 0)
    {
        int ReleasedKey = KeyMap[input];

        switch (ReleasedKey)
        {
        case LShift:
        case Rshift:
            Shift = false;
            // printlnAt(NULL, "SHIFT OFF", 0, 11);
            break;
        }
    }
}

int handleASCII(int PressedKey)
{

    if ('a' <= PressedKey && PressedKey <= 'z')
    {
        if (Mayusc)
            PressedKey += 'A' - 'a';
        if (Shift)
            PressedKey = ShiftKeyMap[PressedKey];
        return PressedKey;
    }
    else if ((' ' <= PressedKey && PressedKey <= '?') || ('Z' < PressedKey && PressedKey < 'a'))
    {
        if (Shift)
            return ShiftKeyMap[PressedKey];
        else
            return PressedKey;
    }

    return -1;
}

void handleCommands(int PressedKey)
{
    if (PressedKey == CapsLock)
    {
        if (Mayusc)
        {
            Mayusc = false;
            // printlnAt(NULL, "CAPS OFF", 0, 10);
        }
        else
        {
            Mayusc = true;
            // printlnAt(NULL, "CAPS ON ", 0, 10);
        }
    }
    else if (PressedKey == LShift || PressedKey == Rshift)
    {
        Shift = true;
        // printlnAt(NULL, "SHIFT ON ", 0, 11);
    }
}