#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

static unsigned int SCREEN_WIDTH = 1024;
static unsigned int SCREEN_HEIGHT = 768;

void drawLine();

void startVideoDriver();

void clearScreen();

void drawChar(int x, int y, char character, int fontColor, int background);

void print(int x,int y,int lenght,int height,int fontColor);

int getHeight();

int getLenght();

#endif