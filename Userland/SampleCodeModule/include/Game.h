#ifndef GAME_H
#define GAME_H

#include <stdio.h>

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

#endif