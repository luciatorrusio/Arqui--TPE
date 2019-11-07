#include "./include/Game.h"

int XMIDDLE = SCREEN_WIDTH/2;                       //la mitad en x de la panalla
int YMIDDLE = SCREEN_HEIGHT/2;                      //la mitad  en y de la pantalla
int R_BLOCKS = 4;                                   //Cantidad de filas de bloques
int C_BLOCKS = 5;                                   //Cantidad de columnas de bloques
enum ballDirec{LU, U, RU, RD, D, LD}ball_direc;     //Left up, up, right up, right down, down, left down
enum walls{NONE = 0, LEFT, RIGHT, UPPER, FLOOR}wall;          //los bordes de la pantalla
int bar_vel= 1;                                     //velocidad de la barra 
int LIVESi = 3;                                     //cantidad de vidas al iniciar el juego    
int lives;                                          //cantidad de vidas que tiene
int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int ball_pos[2];                                    //pelota en el medio de ls pantalla
int ball_vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
int pos_bar;


int runGame(void){
    
    lives = LIVESi;                     
    blocks[R_BLOCKS][C_BLOCKS];         
    ball_pos[]={XMIDDLE, YMIDDLE};      
    ball_vel=1;                         
    pos_bar = XMIDDLE;
    ball_direc = D;

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

int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel, ballDirec ball_direc, int lives){
    
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);

//barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!barHitWall() || barHitWall() == RIGHT){      
             bar_pos  -= bar_vel;                     //la muevo para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall() || barHitWall() == LEFT){
            bar_pos += bar_vel;
        }
    }

//Para la pelota
    switch(wall = ballHitWall()){
        case FLOOR:
            lives -=1; 
            ball_pos[]={XMIDDLE, YMIDDLE};
            pos_bar = XMIDDLE;
            break;
        case LEFT:    
        case RIGHT:
        case UPPER:
            invertDirection(wall);
            break;
        case NONE:
    }
    if(ballHitBlock())

}








/* funciones a hacer=
    .bool left_arrow_pressed()
    .bool right_arrow_pressed()
    .walls barHitWall()               devuelve el wall, (enum walls)
    .walls ballHitWall()                              ""
    .ballHitBlock()                 devuelve la pos del block o [-1, -1] si no le pego a nada
    .print_ball(ball_pos)
    .print_blocks(blocks)
    .print_bar(bar_pos)
    .invertDirectionLR()            hace que la pelotita cambie de direccion si choca con una pared
    .invertDirectionU()

en el if 0=false; 1=true  SORRY TAMI SOY UN DESASTRE

