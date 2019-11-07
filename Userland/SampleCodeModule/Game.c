#include "./include/Game.h"
int X = 0;
int Y = 1;
int XMIDDLE = SCREEN_WIDTH/2;                       //la mitad en x de la panalla
int YMIDDLE = SCREEN_HEIGHT/2;                      //la mitad  en y de la pantalla
int R_BLOCKS = 4;                                   //Cantidad de filas de bloques
int C_BLOCKS = 5;                                   //Cantidad de columnas de bloques
int bar_vel= 1;                                     //velocidad de la barra 
int LIVESi = 3;                                     //cantidad de vidas al iniciar el juego    
int lives;                                          //cantidad de vidas que tiene
int blocks[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
int ball_pos[2];                                    //pelota en el medio de ls pantalla
int ball_vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
int pos_bar;
int BAR_LENGTH;
int NO_BLOCK[]={-1,-1,-1};
int BLOCK_WIDTH;            //COMPLETAR
int BLOCK_XSEPARATION;      //COMPLETAR
int BLOCK_HEIGHT;           //COMPLETAR
int BLOCK_YSEPARATION;      //COMPLETAR


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

 //juega recursivamente

int startGame(int bar_pos,int[R_BLOCKS][C_BLOCKS] blocks, int [2] ball_pos, int ball_vel, ballDirec ball_direc, int lives){
    if(stopKeyPressed()){ //cambiar al menu principal
        mainMenu();
    }

    int block[3];                       // block[0]=posX de bloque que choco, block[1]=posY, block[2]=lado que choco del bloque;
    print_ball(ball_pos);
    print_blocks(blocks);
    print_bar(bar_pos);


    /*MOVIMIENTO DE LA BARRA*/
        //barHitWall devuelve un int que representa que pared esta chocando (enum walls)
    if(left_arrow_pressed()){
       if(!barHitWall() || barHitWall() == RIGHT){      
             bar_pos  -= bar_vel;                     //muevo la barra para la izquierda
       }
    }
    if(right_arrow_pressed()){
        if(!barHitWall() || barHitWall() == LEFT){
            bar_pos += bar_vel;                     //muevo la barra para la derecha
        }
    }

    /*MOVIMIENTO DE LA PELOTA*/
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
    startGame(pos_bar, blocks, ball_pos, ball_vel, ball_direc, lives);
}

void print_blocks(int[R_BLOCKS][C_BLOCKS] blocks){
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            if( blocks[i][j] == 1){
                print_block(i*BLOCK_WIDTH + BLOCK_XSEPARATION, j*BLOCK_HEIGHT + BLOCK_YSEPARATION);
            }
        }
    }
}

void ballHitBarChangeDireccion(barSides side){
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

int[] ballNextPos(){
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


//{LU, U, RU, RD, D, LD}ball_direc;


//walls{NONE = 0, LEFT, RIGHT, UPPER, FLOOR}wall; 

void invertDirection(walls wall){
    switch(wall){
        case LCORNER:
            ball_direc = RD;
        break;
        case RCORNER = LD;
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
    int auxPos[]= ballNextPos();
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            //PARA VER SI ESTA CHOCANDO ARRIBA O ABAJO
            if(auxPos[x] < (i+1)* BLOCK_WIDTH + (i+1)* BLOCK_XSEPARATION && ball_pos[X] > i* BLOCK_WIDTH + (i+1)* BLOCK_XSEPARATION){
                if(auxPos[Y] < (j+1)* BLOCK_HEIGHT + (j+1)*BLOCK_YSEPARATION - BLOCK_HEIGHT/2 && auxPos[Y] > (j)* BLOCK_HEIGHT + (j+1)*BLOCK_YSEPARATION){
                    blocks_left -=1;
                    return {i,j,UPPER };//en verdad es la parte de abajo del bloque pero se comporta como la pared de arriba
                }
                if(auxPos[Y] == (j)* BLOCK_HEIGHT + (j+1)*BLOCK_YSEPARATION + BLOCK_HEIGHT/2 ){
                    blocks_left -=1;
                    return{1,j, FLOOR};
                }
            //PARA VER SI ESTA CHOCANDO EN ALGUN COSTADO    
            }else if()
            
        }
    }
}
wall ballTouchingUpperOrLower(int c, int r){
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
}

int ballBetweenXSides(int[] auxPos, int c, int r){
    if(auxPos[x] < (c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION && auxPos[X] > c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION){
        return 1;
    }
    return 0;
}
int ballBetweenYSides(int[] auxPos, int c, int r){
    if(auxPos[Y] < (r+1)* BLOCK_HEIGHT + (r+1)*BLOCK_YSEPARATION - BLOCK_HEIGHT/2 && auxPos[Y] > (r)* BLOCK_HEIGHT + (r+1)*BLOCK_YSEPARATION)
}

/* funciones a hacer=
    .bool stopKeyPressed()
    .bool left_arrow_pressed()
    .bool right_arrow_pressed()
   
    .int[] ballHitBlock()                  devuelve la pos del block o {-1,-1,-1} si no le pego a nada, resta  blocks_left -=1;
    .print_ball(ball_pos)
    .print_bar(bar_pos) 
    .mainMenu()                             seria la funcion que se corre para mostrar si elegir la terminal o el juego


