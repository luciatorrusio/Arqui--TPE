#ifndef GAME_H
#define GAME_H

#include "gamePrinter.h"
#define R_BLOCKS  8                                  //Cantidad de filas de bloques
#define C_BLOCKS  8                                   //Cantidad de columnas de bloques

struct PieceSet {
    int board[R_BLOCKS][C_BLOCKS];                                    //pelota en el medio de ls pantalla
    int left;
};
struct Board{
    int board[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
    int angle;
};
struct Time{
    int past;                   //tiempo en el juego time_past
    int tick;
};



//devuelve 0 si no fue precionada la tecla especial
int stopKeyPressed();

int left_arrow_pressed();

int right_arrow_pressed();

void print_block(int x, int y,int color);

//Inicialiizar el juego desde cero
int runGame(void);


//para volver si fue pausado
int startGame(void);

void startGameRec(void);

void print_blocks();

void handleBallMov();

void makeSquare(int * square, int x, int y);

int finishGame(int time_past);

void ballNextPos(int * auxPos);

#endif