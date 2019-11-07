#include "./include/Game.h"

int XMIDDLE = SCREEN_WIDTH/2;               //la mitad en x de la panalla
int YMIDDLE = SCREEN_HEIGHT/2;              //la mitad  en y de la pantalla
int R_BLOCKS = 4;                           //Cantidad de filas de bloques
int C_BLOCKS = 5;                           //Cantidad de columnas de bloques
int LIVESi = 3;                             //cantidad de vidas al iniciar el juego
enum ball_direc{LU, U, RU, RD, D, LD};      //Left up, up, right up, right down, down, left down
enum walls{LEFT, RIGHT, UPPER, FLOOR};      //los bordes de la pantalla
int bar_vel= 1;                             //velocidad de la barra 

int runGame(void){
    
    int lives = LIVESi;                     //cantidad de vidas que tiene
    int blocks[R_BLOCKS][C_BLOCKS];         //matriz de los bloques
    int ball_pos[]={XMIDDLE, YMIDDLE};      //pelota en el medio de ls pantalla
    int ball_vel=1;                         //la velocidad cuenta de a cuantos cuadraditos se mueve
    int pos_bar = XMIDDLE;
    

    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks[i][j]= 1;
        }
    }

    /*Inicializo el juego con el estado inicial: 
        status= .pos_barra(x)
                .matrizDeBloques(si esta en 1, sino en 0)
                .pos de pelota(x,y)
                .velocidad de la pelota
                .direccion de pelota (6 posibilidades)
                .cantidad de vidas
    */
    
    
    startGame(pos_bar, blocks, ball_pos, ball_vel, ball_direc, lives);      //inicializa el juego(empieza a pintar la pantalla)
    return 0;
}



 //inicializa el juego(empieza a pintar la pantalla)

int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel, ball_direc, lives){
    
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);

//barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!barHitWall() || Hit() == RIGHT){
             bar_pos  -= bar_vel;                     //la muevo para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall() || Hit() == LEFT){
            bar_pos += bar_vel;
        }
    }

}


