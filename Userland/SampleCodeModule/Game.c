#include "./include/Game.h"
#include "../Include/Time.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include <stdbool.h>

#define LIVESi                      3//cantidad de vidas al iniciar el juego    

#define SCREEN_HEIGHT               600//completar
#define SCREEN_WIDTH                600//completar

#define BAR_LENGTH                  (17*SCREEN_WIDTH/100)
#define BAR_HEIGHT                  (4*SCREEN_HEIGHT/100)                
#define BAR_YPOS                    (78*SCREEN_HEIGHT/100)

#define BLOCK_WIDTH                 ((2*SCREEN_WIDTH/3) / C_BLOCKS)
#define BLOCK_XSEPARATION           ((SCREEN_WIDTH/3) / C_BLOCKS)
#define BLOCK_HEIGHT                ( (SCREEN_HEIGHT/2) / ( R_BLOCKS + 2) )
#define BLOCK_YSEPARATION           ( (2*BLOCK_HEIGHT ) / (R_BLOCKS +2 ))
#define BALL_RADIO                  (1*SCREEN_HEIGHT/200) 

#define bar_vel                     (2*SCREEN_WIDTH/100)

#define REAL_TO_GAME_TICKS              (1)



//COLORES
    #define BLACK                       0x000000
    #define WHITE                       0xFFFFFF
    #define BLUE                        0x1
    #define GREEN                       0x2
    #define AQUA                        0x3
    #define RED                         0x4
    #define PURPLE                      0x5
    #define YELLOW                      0x6
    #define LightBlue                   0x9
    #define LightGreen                  0xA
    #define LightAqua                   0xB
    #define LightRed                    0xC
    #define LightPurple                 0xD
    #define LightYellow                 0xE   
//

#define X                           0
#define Y                           1

#define NO_BLOCK                   -1

#define LEFT_ARROW                 'j'
#define RIGHT_ARROW                'l' 
#define LEAVE_KEY                  'q'


static int lives;                    //cantidad de vidas que tiene

static struct Ball ball;

static int bar_pos[2];

static struct Blocks blocks;

static struct Time time;

int block[3];

static char KeyBuffer[200];
static int keyBufferFront = 0;
static int keyBufferBack = 0;

static bool goToTerminal = false;



//DECLARACION DE FUNCIONES
    void printObjects(int * curr_BallPos, int * curr_BarPos,int * block);
    void printLeftover(int * curr_BarPos);
    int key_pressed();
//

//para inicializar el juego de cero
int runGame(void){
    time.past=0;
    lives = LIVESi;
    blocks.left= R_BLOCKS*C_BLOCKS;                            
    
    ball.pos[X]=SCREEN_WIDTH/2;
    ball.pos[Y]=SCREEN_HEIGHT/2;      
    ball.vel=1;
    ball.dir = D; 
    
    bar_pos[X]=SCREEN_WIDTH/2;
    bar_pos[Y]=BAR_YPOS; 
    
    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks.matrix[j][i]= 1;
        }
    }

    /*comienza el juego  */
    startGame();      
    
    return 0;
}

//cuando quiero retomar el juego
int startGame(){
    int aux;
    setRelativeStartTime();
    time.start[0]=time.relative_start[0];
    time.start[1]=time.relative_start[1];
    time.start[2]=time.relative_start[2];
    time.start[3]=time.relative_start[3];
    time.start[4]=time.relative_start[4];
    time.start[5]=time.relative_start[5];
    print_blocks();

    // GameTick = 2 real tick
    bool stopWhile = false;
    goToTerminal = false;
	uint64_t baseTicks = 0,realTicks = 0, gameTicks = 0, previusTick = 0;

    baseTicks = getTicks();
    do{
        realTicks = getTicks() - baseTicks;
        parseKeyboard();

        if(realTicks % REAL_TO_GAME_TICKS == 0 && realTicks != previusTick){
            gameTicks++;
            previusTick = realTicks;
            if((aux = stopKeyPressed()) || lives==0 || blocks.left == 0){
                // Condicion de retorno
                stopWhile = true;
            }else
            {
                startGameRec();
            }
        }


    }while(!stopWhile);

    if(aux){ 
        time.past += past_time();
        //COMPLETAR!!! TIENE QUE PASAR ALGO
        return 0;
    }
        
    if(lives == 0  || blocks.left == 0 ){
        time.past=past_time();
        finishGame(time.past);
        return 0;        
    } 
    return 0;
}



 //juega recursivamente

void startGameRec(void){ 
    time.relative=(GetSeconds()- time.relative_start[4]) + (GetMinutes()-time.relative_start[3]) *60 + (GetHours() - time.relative_start[2]) * 60 *60 + (GetDayOfMonth()- time.relative_start[1]) *60*60*24 + (GetYear() - time.relative_start[0])*60*60*24*365; 
    /*
    if(time.relative >= 15){
        ball.vel++;
        setRelativeStartTime();
    }
    */
    
    int curr_BallPos[]={ball.pos[X], ball.pos[Y]};
    int curr_BarPos[]={bar_pos[X], bar_pos[Y]};
    
    /*MOVIMIENTO DE LA BARRA*/
    handleBarMov();
    
    /*MOVIMIENTO DE LA PELOTA*/
    handleBallMov();
    //modificar velocidad de 

    printObjects(curr_BallPos, curr_BarPos, block);
}


void printObjects(int * curr_BallPos, int * curr_BarPos,int * block){
    printLeftover(curr_BarPos);
    print_ball(curr_BallPos,BLACK );
    //print_bar(curr_BarPos, BLACK); 
    print_ball(ball.pos, WHITE );
    int x, y;
    if(block[X]!= NO_BLOCK){
        x = ((block[0]+1) * BLOCK_WIDTH) + BLOCK_XSEPARATION*(block[0]+ 1 +1) ;
        y =  (block[1] * BLOCK_HEIGHT) + BLOCK_YSEPARATION*(block[1] +1) ;
        print_block(x, y, BLACK);   
    }
    print_bar(bar_pos, WHITE);
    
}
void printLeftover(int * curr_BarPos){
    int auxPos[]= {0,0};
    int length = bar_pos[X] - curr_BarPos[X];
    if(length > 0){// yendo para la derecha
        auxPos[X] = bar_pos[X] - BAR_LENGTH - length/2;
        auxPos[Y] =  bar_pos[Y];
        printOnScreen(auxPos, BAR_LENGTH, BAR_HEIGHT, BLACK);
    }
    if(length < 0){//yendo para la izquierda
        auxPos[X] = bar_pos[X] + BAR_LENGTH+ length/2;
        auxPos[Y] =  bar_pos[Y];
        printOnScreen(auxPos, BAR_LENGTH, BAR_HEIGHT, BLACK);
    }
    
    
}



void handleBarMov(){
    //barHitWall devuelve un int que representa que pared esta chocando
    int w = barHitWall();
    int key = key_pressed();
    //if(right_arrow_pressed()){
    if(key == RIGHT_ARROW){
        if(!(w == RIGHT)){
            bar_pos[X] += bar_vel;                     //muevo la barra para la derecha
        }
    }
    //if(left_arrow_pressed()){
    if(key== LEFT_ARROW){
        if(!(w == LEFT)){      
             bar_pos[X]  -= bar_vel;                     //muevo la barra para la izquierda
        }
    } 

    if(key == LEAVE_KEY){
        goToTerminal = true;
    }
}

void handleBallMov(void){
    //si pega contra una pared
    walls wall;
    barSides bar_side;
    ballHitBlock(block);            // se fija en donde y en que bloque pego
    if( (wall = ballHitWall()) ){   //NONE = 0 entonces devuelve FALSE
        
        switch(wall){
            case FLOOR:
            case LLCORNER:
            case LRCORNER:
                lives -=1; 
                ball.pos[X]=SCREEN_WIDTH/2;
                ball.pos[Y]=SCREEN_HEIGHT/2;
                ball.dir= D;
                bar_pos[X] = SCREEN_WIDTH/2;
                return;
            break;
            case LEFT:    
            case RIGHT:
            case UPPER:
            case URCORNER:
            case ULCORNER:
                invertDirection(wall);
            break;
        }
    }
    //si pega contra un bloque
    else if(block[0] != NO_BLOCK){      
        blocks.matrix[block[1]][block[0]]=0;
        invertDirection(block[2]);
    }
    //Si pega en la barra
    else if( (bar_side = ballHitBar()) ){
        ballHitBarChangeDireccion(bar_side);
    }
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
    int LLSquare[2];
    int URSquare[2];
    
    makeSquare(LLSquare, bar_Xcord[0], bar_Ycord[1]);  
    makeSquare(URSquare, bar_Xcord[3], bar_Ycord[0]);

    if(!insideSquare(nextPos, LLSquare , URSquare)){
        return N;
    }
    else{
        //dentro de la primer parte de la barra
        
        makeSquare(LLSquare, bar_Xcord[0], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[1], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            if(ballBetween(ball.pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return L;
            }
            return UL;
        }
        //dentro de la segunda parte de la barra

        makeSquare(LLSquare, bar_Xcord[1], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[2], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            return UM;
        }
        //dentro de la TERCER parte de la barra
        
        makeSquare(LLSquare, bar_Xcord[2], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[3], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            if(ballBetween(ball.pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return R;
            }
            return UR;
        }
    }
    return N;
}

void makeSquare(int * square, int x, int y){
    square[X] = x;
    square[Y] = y;
    return;
}

int ballBetween(int auxPos, int y1, int y2){
    if(auxPos <= y2 && auxPos >= y1){
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

void print_blocks(){
    int x;
    int y;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j <R_BLOCKS ; j++){
            x = (i * BLOCK_WIDTH) + BLOCK_XSEPARATION*(i+1) ;
            y =  (j * BLOCK_HEIGHT) + BLOCK_YSEPARATION*(j+1) ;
            if( blocks.matrix[j][i] == 1){
                print_block( x ,y,WHITE);
            }else{
               print_block( x , y,BLACK);
            }
        }
    }
}

void ballHitBarChangeDireccion(barSides side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ballDirec
    switch(side){
        case L:
            ball.dir = LD;
            break;
        case R:
            ball.dir = RU;
            break;
        case UL:
            ball.dir = LU;
            break;
        case UM:
            ball.dir = U;
            break;
        case UR:
            ball.dir = RU;
            break;
    }
}

void ballMove(){
    ballNextPos(ball.pos);
}

void ballNextPos(int * auxPos){
    auxPos[X] = ball.pos[X];
    auxPos[Y] = ball.pos[Y];
    switch(ball.dir){
        case LU:
            auxPos[X] -= ( ball.vel * 0.7071); 
            auxPos[Y] -= ( ball.vel * 0.7071);
            break;
        case U:
            auxPos[Y] -= ball.vel;  
            break;
        case RU:
            auxPos[X] += ( ball.vel * 0.7071); 
            auxPos[Y] -= ( ball.vel * 0.7071);
            break;
        case RD:
            auxPos[X] += ( ball.vel * 0.7071); 
            auxPos[Y] += ( ball.vel * 0.7071);
            break;
        case D: 
            auxPos[Y] += ball.vel;
            break;
        case LD:
            auxPos[X] -= ( ball.vel * 0.7071); 
            auxPos[Y] += ( ball.vel * 0.7071);
            break;
    }
    return;
}
 

void invertDirection(walls wall){
    switch(wall){
        case ULCORNER:
            ball.dir = RD;
        break;
        case URCORNER:
            ball.dir = LD;
        break;
        case LLCORNER:
            ball.dir = RU;
        break;
        case LRCORNER:
            ball.dir = LU;
        break;
        case LEFT:
            if(ball.dir == LU){
                    ball.dir = RU;
            }
            else if( ball.dir == LD){
                ball.dir = RD;
            }
        break;
        case RIGHT:
            if(ball.dir == RU){
                ball.dir = LU;
            }else if(ball.dir == RD){
                ball.dir = LD;
            }
        break;
        case UPPER:
            switch(ball.dir){
                case LU:
                    ball.dir = LD;
                break;
                case RU:
                    ball.dir = RD;
                break;
                case U:
                    ball.dir = D;
                break;
            }
        break;
        //FLOOR SOLO PASA CON LOS BLOQUES(la parte de arriba)
        case FLOOR:
            switch(ball.dir){
                case LD:
                    ball.dir = LU;
                break;
                case RD:
                    ball.dir = RU;
                break;
                case D:
                    ball.dir = U;
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
            if(blocks.matrix[j][i]==1){
                auxWall = ballTouchingWall(i, j);
                if(auxWall){
                    block[0]=i;
                    block[1]=j;
                    block[2]=auxWall;
                    return;
                }
            }       
        }
    }
    block[0]= NO_BLOCK;
    block[1]=NO_BLOCK;
    block[2]=NO_BLOCK;
    return;
}


walls ballTouchingWall(int c, int r){
    
    int nextPos[2];
    ballNextPos(nextPos);
    
    
    if(ballBetweenXSides(nextPos, c, r) && ballBetweenYSides(nextPos, c, r)){
        
        blocks.left -=1;
        
        if( ballBetweenXSides(ball.pos, c, r) ){
            
            if(ball.dir == U || ball.dir == LU || ball.dir == RU){
                
                return UPPER;//en verdad es la parte de abajo del bloque pero se comporta como la pared de arriba
            }
            if(ball.dir == D || ball.dir == LD || ball.dir == RD){
                return FLOOR; //en verdad esta tocando la parte de arriba pero se comporta como piso
            }
        }
        if(ballBetweenYSides(ball.pos, c, r)){
            
            if(ball.dir == LU || ball.dir == LD){
                return LEFT;
            }
            if(ball.dir == RU || ball.dir == RD){
                return RIGHT; 
            }
        }
        if( !ballBetweenYSides(ball.pos, c, r) && !ballBetweenXSides(ball.pos, c, r)){
            
            switch(ball.dir){
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
    }
    
    return NONE;
}

int ballBetweenXSides(int * auxPos, int c, int r){
    int x1=(c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION);
    int x2=( (c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION );

    return ballBetween(auxPos[X], x1, x2 );
}

int ballBetweenYSides(int * auxPos, int c, int r){
    int lowerSideOfBlock = (r+1) * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION - BLOCK_HEIGHT/2 ;
    int upperSideOfBlock =  r * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION;

    return ballBetween(auxPos[Y], upperSideOfBlock, lowerSideOfBlock); 
}


int finishGame(int time_past){
    if(blocks.left == 0){
       // printf("congratulations you've won!! it took you %d seconds", time_past);
    }else{
        //printf("better luck next time! time: %d seconds", time_past);
    }
    return 0;
}

int past_time(){
    return (time.relative + time.relative_start[0] - time.start[0] + time.relative_start[1] - time.start[1] + time.relative_start[2] - time.start[2] + time.relative_start[3] - time.start[3] + time.relative_start[4] - time.start[4]);
}


void setRelativeStartTime(){
    time.relative_start[0]=GetYear();
    time.relative_start[1]=GetMonth();
    time.relative_start[2]= GetDayOfMonth();
    time.relative_start[3]= GetHours();
    time.relative_start[4]= GetMinutes();
    time.relative_start[5]= GetSeconds();
}

void print_ball(int * ball_pos,int color){
    printOnScreen(ball_pos,BALL_RADIO*2,BALL_RADIO*2,color);
}

void print_bar(int * bar_pos,int color){
    printOnScreen(bar_pos,BAR_LENGTH,BAR_HEIGHT,color);
}

void print_block(int x,int y,int color){
    int pos[]= {x, y};
    printOnScreen(pos,BLOCK_WIDTH,BLOCK_HEIGHT,color);
}

int stopKeyPressed(){

    return goToTerminal;
    // char key = readKey();
    // if(key == LEAVE_KEY){
    //     return 1;
    // }
    // return 0;
}




void parseKeyboard(){
    if(keyBufferFront + 1 == keyBufferBack )
        keyBufferBack++;
        
    int temp = readKey();

    if(temp == LEFT_ARROW || temp == RIGHT_ARROW || temp == LEAVE_KEY)
        KeyBuffer[keyBufferFront++ % 200] = temp;

}

int key_pressed(){


    if(keyBufferFront == keyBufferBack)
        return -1;
        
    return KeyBuffer[keyBufferBack++ % 200];


}
