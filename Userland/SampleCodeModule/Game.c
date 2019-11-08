#include "./include/Game.h"
#include "../Include/Time.h"

#define LIVESi  3                                     //cantidad de vidas al iniciar el juego    

#define BAR_LENGTH

#define BLOCK_WIDTH            //COMPLETAR
#define BLOCK_XSEPARATION      //COMPLETAR
#define BLOCK_HEIGHT         //COMPLETAR
#define BLOCK_YSEPARATION      //COMPLETAR


int X = 0;
int Y = 1;

int WON=1;
int LOST =0;

int lives;                                          //cantidad de vidas que tiene

int ball_pos[2];                                    //pelota en el medio de ls pantalla
int ball_vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
ball_dir ball_direc;
int bar_vel= 1;                                     //velocidad de la barra 
int bar_pos;

int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int NO_BLOCK[]={-1,-1,-1};


int time_past;
int relative_startTime;
int relative_time;




//para inicializar el juego
int runGame(void){
    time_past=0;
    lives = LIVESi;                     
    //blocks[R_BLOCKS][C_BLOCKS];         
    ball_pos[0]=SCREEN_WIDTH/2;
    ball_pos[1]=SCREEN_HEIGHT/2;      
    ball_vel=1;                         
    bar_pos=XMIDDLE; //pos_bar = XMIDDLE; QUISISTE DECIR ESO?
    ball_direc = D; //la variable se llama igual al tipo, entonces le cambio el nombre al tipo por dir y declaro aca

    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks[i][j]= 1;
        }
    }

    /*comienza el juego  */
    startGame();      
    return 0;
}

//cuando quiero retomar el juego
int startGame(){
    relative_startTime={GetYear(), GetDay(), GetHour(), GetMinutes(), GetSeconds()};
    start_time = relative_startTime;
    startGameRec();
    return 0;
}



 //juega recursivamente

int startGameRec(void){ 
    
    relative_time=(GetSeconds()- relative_startTime[4]) + (GetMinutes()-relative_startTime[3]) *60) + (GetHours() - relative_startTime[2]) * 60 *60 + (GetDay()- relative_startTime[1]) *60*60*24 + (GetYear() - relative_startTime[0])*60*60*24*365; 
    if(stopKeyPressed()){ 
        time_past += past_time();
        //mainMenu(); esto va?
        return 0;
    }
    if(lives == 0){
        time_past=past_time();
        finishGame(time_past, LOST);
        return 0;        
    }
    if(blocks_left == 0){
        time_past=past_time();
        finishGame(time_past, WON);
        return 0;
    }

    // block[0]=posX de bloque que choco, block[1]=posY, block[2]=lado que choco del bloque;
    int block[3];                       
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);

    /*MOVIMIENTO DE LA BARRA*/
    handleBarMov();
    /*MOVIMIENTO DE LA PELOTA*/
        handleBallMov(block);
    //modificar velocidad de 

    if(relative_time >= 15){
        ball_vel++;
        relative_startTime={GetYear(), GetDay(), GetHour(), GetMinutes(), GetSeconds()};
    }


    startGameRec();
}

void handleBarMov(){
        //barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!(barHitWall() == LEFT)){      
             bar_pos  -= bar_vel;                     //muevo la barra para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall()== RIGHT)){
            bar_pos += bar_vel;                     //muevo la barra para la derecha
        }
    }

}
void handleBallMov(int * block){
            //si pega contra una pared
    switch(wall = ballHitWall()){
        case NONE:
            ball_move();
        case FLOOR:
            lives -=1; 
            ball_pos[]={XMIDDLE, YMIDDLE};
            ball_direc= D;
            pos_bar = XMIDDLE;
            break;
        case LEFT:    
        case RIGHT:
        case UPPER:
            invertDirection(wall);
            ball_move();
            break;
    }
    //si pega contra un bloque
    block=ballHitBlock();
    if(block != NO_BLOCK){    
        blocks[block[0]][block[1]]=0;
        invertDirection(block[2]); //acordarse que si pega en la derecha tiene que devolver wall = LEFT
        ball_move();
    }else{
        ball_move();
    }
    //Si pega en la barra
    if(bar_side = ballHitBar()){
        ballHitBarChangeDireccion(bar_side);
        ball_move();
    }else{
        ball_move();
    }
}

void print_blocks(int blocks[R_BLOCKS][C_BLOCKS]){
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            if( blocks[i][j] == 1){
                print_block(i*BLOCK_WIDTH + BLOCK_XSEPARATION, j*BLOCK_HEIGHT + BLOCK_YSEPARATION);
            }
        }
    }
}

void ballHitBarChangeDireccion(bar_side side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ball_direc
    switch(side){
        case L:
            ball_direc = LD;
            break;
        case R:
            ball_direc = RD;
            break;
        case UL:
            ball_direc = LU;
            break;
        case UM:
            ball_direc = U;
            break;
        case UR:
            ball_direc = RU;
            break;
    }
}

void ballMove(){
     int auxPos[] = ballNextPos();
}

int * ballNextPos(){
    int auxPos[] =ball_pos; 
    switch(ball_direc){
        case LU:
            auxPos[X] -= ( ball_vel * 0,7071); 
            auxPos[Y] += ( ball_vel * 0,7071);
            break;
        case U:
            auxPos[Y] += ball_vel;  
            break;
        case RU:
            auxPos[X] += ( ball_vel * 0,7071); 
            auxPos[Y] += ( ball_vel * 0,7071);
            break;
        case RD:
            auxPos[X] += ( ball_vel * 0,7071); 
            auxPos[Y] -= ( ball_vel * 0,7071);
            break;
        case D: 
            auxPos[Y] += ball_vel * 0,7071;
            break;
        case LD:
            auxPos[X] -= ( ball_vel * 0,7071); 
            auxPos[Y] -= ( ball_vel * 0,7071);
            break;
    }
    return auxPos;
}
 

void invertDirection(walls wall){
    switch(wall){
        case ULCORNER:
            ball_direc = RD;
        break;
        case URCORNER:
            ball-direc = LD;
        break;
        case LLCORNER:
            ball-direc = RU;
        break;
        case LRCORNER:
            ball-direc = LU;
        break;
        case LEFT:
            switch(ball_direc){
                case LU:
                    ball_direc = RU;
                break;
                case LD:
                    ball_direc = RD;
                break;
            }
        break;
        case RIGHT:
            switch(ball_direc){
                case RU:
                    ball_direc = LU;
                break;
                case RD:
                    ball_direc = LD;
                break;
            }
        break;
        case UPPER:
            switch(ball_direc){
                case LU:
                    ball_direc = LD;
                break;
                case RU:
                    ball_direc = RD;
                break;
                case U:
                    ball_direc = D;
                break;
            }
        break;
        //FLOOR SOLO PASA CON LOS BLOQUES(la parte de arriba)
        case FLOOR:
            switch(ball_direc){
                case LD:
                    ball_direc = LU;
                break;
                case RD:
                    ball_direc = RU;
                break;
                case D:
                    ball_direc = U;
                break;
            }
        break;

    }
}

walls ballHitWall(){
    int auxPos[] = ballNextPos();
    if(auxPos[X] + BALL_RADIO >= SCREEN_WIDTH ){
        return RIGHT;
    }else if(auxPos[X] - BALL_RADIO <= 0){
        return LEFT;
    }else if(auxPos[Y] + BALL_RADIO >= SCREEN_HEIGHT){
        return FLOOR;
    }else if(auxPos[Y] - BALL_RADIO <= 0 ){
        return UPPER;
    }else{
        return NONE;
    }
}

walls barHitWall(){
    if(bar_pos+ bar_vel + BAR_LENGTH/2 >= SCREEN_WIDTH){
        return RIGHT;
    }else if(bar_pos -bar_vel- BAR_LENGTH/2 <= 0){
        return LEFT;
    }else{
        return NONE;
    }
}

int[] ballHitBlock(){
    walls auxWall;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            auxWall = ballTouchingWall(i, j);
            if(auxWall){
                return {i,j, auxWall};
            }       
        }
    }
}


wall ballTouchingWall(int c, int r){
    int auxPos[]=ballNextPos();
    if(ballBetweenXSides(auxPos, c, r) && ballBetweenXSides(ball_pos, c, r) && ballBetweenYSides(auxPos, c, r)){
        blocks_left -=1;
        if(ball_direc == U || ball_direc == LU || ball_direc == RU){
            return UPPER;//en verdad es la parte de abajo del bloque pero se comporta como la pared de arriba
        }
        if(ball_direc == D || ball_direc == LD || ball_direc == RD){
            return FLOOR; //en verdad esta tocando la parte de arriba pero se comporta como piso
        }
    }
    if(ballBetweenYSides(auxPos, c, r) && ballBetweenYSides(ball_pos) && ballBetweenXSides(auxPos)){
        blocks_left -=1;
        if(ball_direc == LU || ball_direc == LD){
            return LEFT;
        }
        if(ball_direc == RU || ball_direc == RD){
            return RIGHT; 
        }
    }if(ballBetweenXSides(auxPos, c, r) && ballBetweenYSides(auxPos) && !ballBetweenYSides(ball_pos, c, r) && !ballBetweenXSides(ball_pos, c, r)){
        blocks_left -=1;
        switch(ball_direc){
            case LU:
                return ULCORNER;    
            break;
            case RU:
                return URCORNER;
            break;
            case LD:
                return  LLCORNER;
            break;
            case RD:
                return LRCORNER;
            break;
            
        }else
            return NONE;
    }
}

int ballBetweenXSides(int * auxPos, int c, int r){
    if(((auxPos[x] - BALL_RADIO) < ((c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION)) && ((auxPos[X] + BALL_RADIO) > (c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION))){
        return 1;
    }
    return 0;
}

int ballBetweenYSides(int * auxPos, int c, int r){
    if(((auxPos[Y] - BALL_RADIO) < ((r+1) * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION - BLOCK_HEIGHT/2)) && ((auxPos[Y] + BALL_RADIO) > ((r)* BLOCK_HEIGHT + (r+1)*BLOCK_YSEPARATION))){
        return 1;
    }
    return 0;
}


int finishGame(int time_past, int result){
    if(result == WON)
        printf("congratulations you've won!! it took you %d seconds", time_past);
    else
        printf("better luck next time! time: %d seconds", time_past);
}

int past_time(){
    return relative_time + relative_startTime[0] - start_time[0] + relative_startTime[1] - start_time[1] + relative_startTime[2] - start_time[2] + relative_startTime[3] - start_time[3] + relative_startTime[4] - start_time[4];
}



/* funciones a hacer=
    .bool stopKeyPressed()
    .bool left_arrow_pressed()
    .bool right_arrow_pressed()
    .print_ball(ball_pos)
    .print_bar(bar_pos) 
    .mainMenu()                             seria la funcion que se corre para mostrar si elegir la terminal o el juego

*/
