#include "./include/Game.h"
#include "../Include/Time.h"

#define LIVESi  3                                     //cantidad de vidas al iniciar el juego    

<<<<<<< HEAD
#define BAR_LENGTH

#define BLOCK_WIDTH            //COMPLETAR
#define BLOCK_XSEPARATION      //COMPLETAR
#define BLOCK_HEIGHT         //COMPLETAR
#define BLOCK_YSEPARATION      //COMPLETAR
=======
#define BAR_LENGTH             7//complestar
#define BAR_YPOS               8//completar                

#define BLOCK_WIDTH            7//COMPLETAR
#define BLOCK_XSEPARATION      7//COMPLETAR
#define BLOCK_HEIGHT           7//COMPLETAR
#define BLOCK_YSEPARATION      7//COMPLETAR
>>>>>>> lucia


int X = 0;
int Y = 1;

int WON=1;
int LOST =0;

int lives;                                          //cantidad de vidas que tiene

int ball_pos[2];                                    //pelota en el medio de ls pantalla
int ball_vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
<<<<<<< HEAD
ball_dir ball_direc;
int bar_vel= 1;                                     //velocidad de la barra 
int bar_pos;

int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int NO_BLOCK[]={-1,-1,-1};

=======
ballDirec ball_dir;
int BALL_RADIO;

int bar_vel= 1;                                     //velocidad de la barra 
int* bar_pos;

int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int NO_BLOCK[]={-1,-1,-1};
int blocks_left=R_BLOCKS*C_BLOCKS;
>>>>>>> lucia

int time_past;
int relative_startTime[6];
int relative_time;
int start_time[6];

int SCREEN_HEIGHT; 
int SCREEN_WIDTH;


//para inicializar el juego
int runGame(void){
    time_past=0;
<<<<<<< HEAD
    lives = LIVESi;                     
    //blocks[R_BLOCKS][C_BLOCKS];         
    ball_pos[0]=SCREEN_WIDTH/2;
    ball_pos[1]=SCREEN_HEIGHT/2;      
    ball_vel=1;                         
    bar_pos=XMIDDLE; //pos_bar = XMIDDLE; QUISISTE DECIR ESO?
    ball_direc = D; //la variable se llama igual al tipo, entonces le cambio el nombre al tipo por dir y declaro aca
=======
    lives = LIVESi;                            
    ball_pos[0]=SCREEN_WIDTH/2;
    ball_pos[1]=SCREEN_HEIGHT/2;      
    ball_vel=1;                         
    bar_pos[]={SCREEN_WIDTH/2, BAR_YPOS}; 
    ball_dir = D; //la variable se llama igual al tipo, entonces le cambio el nombre al tipo por dir y declaro aca
>>>>>>> lucia

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
    setRelativeStartTime();
    start_time[0]=relative_startTime[0];
    start_time[1]=relative_startTime[1];
    start_time[2]=relative_startTime[2];
    start_time[3]=relative_startTime[3];
    start_time[4]=relative_startTime[4];
    start_time[5]=relative_startTime[5];
    startGameRec();
    return 0;
}



 //juega recursivamente

int startGameRec(void){ 
    
    relative_time=(GetSeconds()- relative_startTime[4]) + (GetMinutes()-relative_startTime[3]) *60 + (GetHours() - relative_startTime[2]) * 60 *60 + (GetDayOfMonth()- relative_startTime[1]) *60*60*24 + (GetYear() - relative_startTime[0])*60*60*24*365; 
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
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);

    /*MOVIMIENTO DE LA BARRA*/
    handleBarMov();
    /*MOVIMIENTO DE LA PELOTA*/
<<<<<<< HEAD
        handleBallMov(block);
=======
    handleBallMov();
>>>>>>> lucia
    //modificar velocidad de 

    if(relative_time >= 15){
        ball_vel++;
<<<<<<< HEAD
        relative_startTime={GetYear(), GetDay(), GetHour(), GetMinutes(), GetSeconds()};
=======
        setRelativeStartTime();
>>>>>>> lucia
    }


    startGameRec();
<<<<<<< HEAD
=======
    return 1; //no tendria que llegar aca, es para evitar el warning, esta mal asi?
>>>>>>> lucia
}

void handleBarMov(){
        //barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!(barHitWall() == LEFT)){      
<<<<<<< HEAD
             bar_pos  -= bar_vel;                     //muevo la barra para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall()== RIGHT)){
            bar_pos += bar_vel;                     //muevo la barra para la derecha
=======
             bar_pos[X]  -= bar_vel;                     //muevo la barra para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!(barHitWall()== RIGHT)){
            bar_pos[X] += bar_vel;                     //muevo la barra para la derecha
>>>>>>> lucia
        }
    }

}
<<<<<<< HEAD
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
=======
void handleBallMov(void){
    //si pega contra una pared
    walls wall;
    barSides bar_side;
    int block[3];
    ballHitBlock(block);
    if( (wall = ballHitWall()) ){   //NONE = 0 entonces devuelve FALSE
        switch(wall){
            case FLOOR:
                lives -=1; 
                ball_pos[0]=SCREEN_WIDTH/2;
                ball_pos[0]=SCREEN_HEIGHT/2;
                ball_dir= D;
                bar_pos[X] = SCREEN_WIDTH/2;
                return;
>>>>>>> lucia
            break;
            case LEFT:    
            case RIGHT:
            case UPPER:
                invertDirection(wall);
            break;
            case URCORNER:
                ball_dir = LD;
            break;
            case ULCORNER:
                ball_dir = RD;
            break;
            case NONE:
            case LRCORNER:
            case LLCORNER:
            break;
        }
    }
    //si pega contra un bloque
    else if(block != NO_BLOCK){    
        blocks[block[0]][block[1]]=0;
        invertDirection(block[2]); //acordarse que si pega en la derecha tiene que devolver wall = LEFT
    }
    //Si pega en la barra
    else if( (bar_side = ballHitBar()) ){
        ballHitBarChangeDireccion(bar_side);
    }
<<<<<<< HEAD
}

void print_blocks(int blocks[R_BLOCKS][C_BLOCKS]){
=======
    ballMove();
}

/*typedef enum barSides{N = 0, L, R, UL, UM, UR} barSides;      
             ____________________________________ bar_Ycord[0]
            |___________|_____-______|___________| <-bar      __ bar_Ycord[1]
     bar_Xcord[0]  bar_Xcord[1]  bar_Xcord[2]  bar_Xcord[3]
                               ^
                               |
                            bar_pos
*/
barSides ballHitBar(){
    int bar_Xcord[]={bar_pos[X] - BAR_LENGTH/2, bar_pos[X] - BAR_LENGTH/6, bar_pos[X] + BAR_LENGTH/6, bar_pos[X] + BAR_LENGTH/2};
    int bar_Ycord[] = {bar_pos[Y] - BAR_HEIGHT / 2, bar_pos[Y] + BAR_HEIGHT / 2 };
    int nextPos[2];
    ballNextPos(nextPos);
    if(!insideSquare(nextPos, {bar_Xcord[0], bar_Ycord[1]}, {bar_Xcord[3], bar_Ycord[0]})){
        return N;
    }else{
        //dentro de la primer parte de la barra
        if(insideSquare(nextPos, {bar_Xcord[0], bar_Ycord[1]}, {bar_Xcord[1], bar_Ycord[0]})){
            if(ballBetween(ball_pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return L;
            }
            return UL;
        }
        //dentro de la segunda parte de la barra
        if(insideSquare(nextPos, {bar_Xcord[1], bar_Ycord[1]}, {bar_Xcord[2], bar_Ycord[0]})){
            return UM;
        }
        //dentro de la TERCER parte de la barra
        if(insideSquare(nextPos, {bar_Xcord[2], bar_Ycord[1]}, {bar_Xcord[3], bar_Ycord[0]})){
            if(ballBetween(ball_pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return R;
            }
            return UR;
        }
    }
}

int ballBetween(int auxPos, int y1, int y2){
    if(auxPos < y2 && auxPos > y1){
        return 1;
    }
    return 0;
}

//la pos de la pelota, punto de abajo a la izquierda y arriba a la derecha del cuadrado
int insideSquare(int * auxPos, int * LLSquare, int * URSquare){
    if(ballBetween(auxPos[X],LLSquare[X], URSquare[X]) && ballBetween(auxPos[Y], URSquare[Y], LLSquare[Y])){
        return 1;
    }
    return 0;
}

void print_blocks(int blocks[R_BLOCKS][C_BLOCKS]){
    int x;
    int y;
>>>>>>> lucia
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            if( blocks[i][j] == 1){
                x = (i * BLOCK_WIDTH) + BLOCK_XSEPARATION ;
                y =  (j * BLOCK_HEIGHT) + BLOCK_YSEPARATION ;
                print_block( x , y );
            }
        }
    }
}

<<<<<<< HEAD
void ballHitBarChangeDireccion(bar_side side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ball_direc
=======
void ballHitBarChangeDireccion(barSides side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ballDirec
>>>>>>> lucia
    switch(side){
        case L:
            ball_dir = LD;
            break;
        case R:
            ball_dir = RD;
            break;
        case UL:
            ball_dir = LU;
            break;
        case UM:
            ball_dir = U;
            break;
        case UR:
            ball_dir = RU;
            break;
    }
}

void ballMove(){
    ballNextPos(ball_pos);
}

<<<<<<< HEAD
int * ballNextPos(){
    int auxPos[] =ball_pos; 
    switch(ball_direc){
=======
void ballNextPos(int * auxPos){
    auxPos[X] =ball_pos[X];
    auxPos[Y] = ball_pos[Y]; 
    switch(ball_dir){
>>>>>>> lucia
        case LU:
            auxPos[X] -= ( ball_vel * 0.7071); 
            auxPos[Y] += ( ball_vel * 0.7071);
            break;
        case U:
            auxPos[Y] += ball_vel;  
            break;
        case RU:
            auxPos[X] += ( ball_vel * 0.7071); 
            auxPos[Y] += ( ball_vel * 0.7071);
            break;
        case RD:
            auxPos[X] += ( ball_vel * 0.7071); 
            auxPos[Y] -= ( ball_vel * 0.7071);
            break;
        case D: 
            auxPos[Y] += ball_vel * 0.7071;
            break;
        case LD:
            auxPos[X] -= ( ball_vel * 0.7071); 
            auxPos[Y] -= ( ball_vel * 0.7071);
            break;
    }
    return;
}
 

void invertDirection(walls wall){
    switch(wall){
        case ULCORNER:
            ball_dir = RD;
        break;
        case URCORNER:
            ball_dir = LD;
        break;
        case LLCORNER:
            ball_dir = RU;
        break;
        case LRCORNER:
            ball_dir = LU;
        break;
        case LEFT:
            if(ball_dir == LU){
                    ball_dir = RU;
            }
            else if( ball_dir == LD){
                ball_dir = RD;
            }
        break;
        case RIGHT:
            if(ball_dir == RU){
                ball_dir = LU;
            }else if(ball_dir == RD){
                ball_dir = LD;
            }
        break;
        case UPPER:
            switch(ball_dir){
                case LU:
                    ball_dir = LD;
                break;
                case RU:
                    ball_dir = RD;
                break;
                case U:
                    ball_dir = D;
                break;
            }
        break;
        //FLOOR SOLO PASA CON LOS BLOQUES(la parte de arriba)
        case FLOOR:
            switch(ball_dir){
                case LD:
                    ball_dir = LU;
                break;
                case RD:
                    ball_dir = RU;
                break;
                case D:
                    ball_dir = U;
                break;
            }
        break;

    }
}



//implementar CORNERS
walls ballHitWall(){
    int auxPos[2];
    ballNextPos(auxPos);
    if(auxPos[X] + BALL_RADIO >= SCREEN_WIDTH ){
        return RIGHT;
    }else if(auxPos[X] - BALL_RADIO <= 0){
        return LEFT;
    }else if(auxPos[Y] + BALL_RADIO >= SCREEN_HEIGHT){
        return FLOOR;
    }else if(auxPos[Y] - BALL_RADIO <= 0 ){
        return UPPER;
    }
    return NONE;
}

walls barHitWall(){
    if( ( bar_pos[X]+ bar_vel + (BAR_LENGTH /2) ) >= SCREEN_WIDTH){
        return RIGHT;
    }else if(bar_pos[X] -bar_vel- BAR_LENGTH/2 <= 0){
        return LEFT;
    }
    return NONE;
}

void ballHitBlock(int * block){
    walls auxWall;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            auxWall = ballTouchingWall(i, j);
            if(auxWall){
                block[0]=i;
                block[1]=j;
                block[2]=auxWall;
            }       
        }
    }
    return;
}


walls ballTouchingWall(int c, int r){
    int auxPos[2];
    ballNextPos(auxPos);
    if(ballBetweenXSides(auxPos, c, r) && ballBetweenXSides(ball_pos, c, r) && ballBetweenYSides(auxPos, c, r)){
        blocks_left -=1;
        if(ball_dir == U || ball_dir == LU || ball_dir == RU){
            return UPPER;//en verdad es la parte de abajo del bloque pero se comporta como la pared de arriba
        }
        if(ball_dir == D || ball_dir == LD || ball_dir == RD){
            return FLOOR; //en verdad esta tocando la parte de arriba pero se comporta como piso
        }
    }
    if(ballBetweenYSides(auxPos, c, r) && ballBetweenYSides(ball_pos, c, r) && ballBetweenXSides(auxPos, c, r)){
        blocks_left -=1;
        if(ball_dir == LU || ball_dir == LD){
            return LEFT;
        }
        if(ball_dir == RU || ball_dir == RD){
            return RIGHT; 
        }
    }if(ballBetweenXSides(auxPos, c, r) && ballBetweenYSides(auxPos, c, r) && !ballBetweenYSides(ball_pos, c, r) && !ballBetweenXSides(ball_pos, c, r)){
        blocks_left -=1;
        switch(ball_dir){
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
            
        }
    }
    return NONE;
}

int ballBetweenXSides(int * auxPos, int c, int r){
<<<<<<< HEAD
    if(((auxPos[x] - BALL_RADIO) < ((c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION)) && ((auxPos[X] + BALL_RADIO) > (c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION))){
=======
    if(((auxPos[X] - BALL_RADIO) < ((c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION)) && ((auxPos[X] + BALL_RADIO) > (c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION))){
>>>>>>> lucia
        return 1;
    }
    return 0;
}

int ballBetweenYSides(int * auxPos, int c, int r){
<<<<<<< HEAD
    if(((auxPos[Y] - BALL_RADIO) < ((r+1) * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION - BLOCK_HEIGHT/2)) && ((auxPos[Y] + BALL_RADIO) > ((r)* BLOCK_HEIGHT + (r+1)*BLOCK_YSEPARATION))){
        return 1;
    }
    return 0;
=======
    int topOfBall= auxPos[Y] - BALL_RADIO;
    int bottomOfBall = auxPos[Y] + BALL_RADIO;
    int lowerSideOfBlock = (r+1) * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION - BLOCK_HEIGHT/2 ;
    int upperSideOfBlock =  r * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION;
    return   (topOfBall < lowerSideOfBlock) || ( bottomOfBall > upperSideOfBlock ); 
>>>>>>> lucia
}


int finishGame(int time_past, int result){
    if(result == WON){
        printf("congratulations you've won!! it took you %d seconds", time_past);
    }else{
        printf("better luck next time! time: %d seconds", time_past);
    }
    return 0;
}

int past_time(){
    return (relative_time + relative_startTime[0] - start_time[0] + relative_startTime[1] - start_time[1] + relative_startTime[2] - start_time[2] + relative_startTime[3] - start_time[3] + relative_startTime[4] - start_time[4]);
}

<<<<<<< HEAD
int past_time(){
    return relative_time + relative_startTime[0] - start_time[0] + relative_startTime[1] - start_time[1] + relative_startTime[2] - start_time[2] + relative_startTime[3] - start_time[3] + relative_startTime[4] - start_time[4];
=======

void setRelativeStartTime(){
    relative_startTime[0]=GetYear();
    relative_startTime[1]=GetMonth();
    relative_startTime[2]= GetDayOfMonth();
    relative_startTime[3]= GetHours();
    relative_startTime[4]= GetMinutes();
    relative_startTime[5]= GetSeconds();
>>>>>>> lucia
}



/* funciones a hacer=
    .printf();
    .bool stopKeyPressed()
    .bool left_arrow_pressed()
    .bool right_arrow_pressed()
    .print_ball(ball_pos)
    .print_bar(bar_pos) 
    .mainMenu()                             seria la funcion que se corre para mostrar si elegir la terminal o el juego
<<<<<<< HEAD

=======
    .barSides ballHitBar()
>>>>>>> lucia
*/
