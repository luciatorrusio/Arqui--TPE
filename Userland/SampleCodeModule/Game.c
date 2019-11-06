#include "./include/Game.h"

int MIDDLE = SCREEN_WIDTH/2;
int F_BLOQUES = 4; //Cantidad de filas de bloques
int C_BLOQUES = 5; //Cantidad de columnas de bloques

int runGame(void){
    int bloques[F_BLOQUES][C_BLOQUES];  //matriz de los bloques

    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(i=0; i<F_BLOQUES ; i++){
        for(j=0; j<C_BLOQUES; j++){
            bloques[i][j]=1;
        }
    }


    //Inicializo el estado: 
    //status= {pos_barra(x), matrizDeBloques(si esta en 1, sino en 0), pos de pelota(x,y)}

    int status[]={MIDDLE, bloques,  } 
}