#ifndef GAME_H
#define GAME_H

#include <stdio.h>
enum ballDirec{LU, U, RU, RD, D, LD}ball_direc;     //Left up, up, right up, right down, down, left down
enum walls{NONE = 0, LEFT, RIGHT, UPPER, FLOOR, RCORNER, LCORNER}wall;          //los bordes de la pantalla
enum barSides{N, L, R, UL, UM, UR}bar_side;                    //none, left, right, upperLeft, UpperMiddle, UpperRight

int runGame(void);


int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel,int ball_direc,int lives);


void print_blocks(int[R_BLOCKS][C_BLOCKS] blocks);


/*Le cambia la direccion a la pelota dependiendo exactamente donde cae en la barra
    Si cae en la parte de arriba la barra se divide en tres:
        A la izquierda: va a salir 135 grados(LU)
        En el medio a 90 grados(arriba, U)
        A la derecha a 45gados(RU)
    si cae en uno de los lados:
        derecha: sale a -45 grados(RD)
        izquierda: sale a 225 grados(RD)
*/
void ballHitBarChangeDireccion(barSides side);

//Le cambia la posicion a la pelota dependiendo su pos y direccion y vel
void ballMove();


//hace que la pelotita cambie de direccion si choca con una pared o bloque
void invertDirection(walls wall);

#endif