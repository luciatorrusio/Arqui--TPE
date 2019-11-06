#include "./include/Game.h"

int XMIDDLE = SCREEN_WIDTH/2;  
int YMIDDLE = SCREEN_HEIGHT/2;
int R_BLOCKS = 4; //Cantidad de filas de bloques
int C_BLOCKS = 5; //Cantidad de columnas de bloques
int LIVESi = 3;     //cantidad de vidas al iniciar el juego
enum ball_direc{LU, U, RU, RD, D, LD}; //Left up, up, right up, right down, down, left down
int runGame(void){
    int lives = LIVESi;                      //cantidad de vidas que tiene
    int blocks[R_BLOCKS][C_BLOCKS];  //matriz de los bloques
    int ball_pos[]={XMIDDLE, YMIDDLE};  //pelota en el medio de ls pantalla
    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < R_BLOCKS ; i++){
        for(int j = 0; j < C_BLOCKS; j++){
            blocks[i][j]= 1;
        }
    }

    /*Inicializo el estado: 
        status= .pos_barra(x)
                .matrizDeBloques(si esta en 1, sino en 0)
                .pos de pelota(x,y)
                .direccion de pelota (6 posibilidades)
                .cantidad de vidas
    */
    int status[]={XMIDDLE, blocks, ball_pos, D, lives};




}



