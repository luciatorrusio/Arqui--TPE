#include "./include/Game.h"
#include "../Include/Time.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/deviceInfo.h"
#include <stdbool.h>
#include "./include/Speaker.h"

#define LIVESi                      3//cantidad de vidas al iniciar el juego    

#define BAR_LENGTH                  (17*SCREEN_WIDTH/100)
#define BAR_HEIGHT                  (4*SCREEN_HEIGHT/200)                
#define BAR_YPOS                    (78*SCREEN_HEIGHT/100)

#define BLOCK_WIDTH                 (SCREEN_HEIGHT/9)
#define BLOCK_XSEPARATION           (0)
#define BLOCK_HEIGHT                (SCREEN_HEIGHT/9)
#define BLOCK_YSEPARATION           (0)

#define BALL_RADIO                  (SCREEN_HEIGHT/100) 

#define bar_vel                     (2*SCREEN_WIDTH/100)

#define REAL_TO_GAME_TICKS              (1)
#define BALL_INITIAL_VELOCITY (3)

enum pieces1 {PAWN1, BISHOP1, KNIGHT1, ROOK1, QUEEN1, KING1};
enum pieces2 {PAWN2=200, BISHOP2, KNIGHT2, ROOK2, QUEEN2, KING2};
//COLORES
    #define BLACK                       0x000000
    #define WHITE                       0xFFFFFF
    #define BLUE                        0x0000FF
    #define GREEN                       0x00FF00
    #define AQUA                        0x00FFFF
    #define RED                         0xFF0000
    #define PURPLE                      0XBB00FF
    #define YELLOW                      0xFFFF00
    #define LightBlue                   0x6677FF
    #define LightGreen                  0x33FF44
    #define LightRed                    0xFF00FF
    #define LightPurple                 0x7700FF
  
//

#define X                           0
#define Y                           1

#define NO_BLOCK                   -1

#define LEFT_ARROW                 'j'
#define RIGHT_ARROW                'l' 
#define UP_ARROW                   'i'
#define DOWN_ARROW                 'k'
#define ENTER                      '\n'
#define LEAVE_KEY                  'q'


static int lives = -1;                    //cantidad de vidas que tiene

static struct Ball ball={{-1,-1},-1,-1};

static int usr_pos[2] = {-1,-1};
static int curr_usr = 0;


static struct Blocks blocks = {-1,-1};

static struct Time time={-1,-1};

int block[3]={-1,-1,-1};

static char KeyBuffer[200];
static int keyBufferFront = 0;
static int keyBufferBack = 0;

static bool goToTerminal = false;

static int SCREEN_HEIGHT= -1;
static int SCREEN_WIDTH= -1;
static int info[2]={-1,-1};

static uint64_t gameTicks = -1;

static int initialize= -1;
//DECLARACION DE FUNCIONES
    void printObjects(int * block);
    void printLeftover(int * curr_BarPos);
    int key_pressed();
    void parseKeyboard();
    bool limitInput(char ch);
    void table();
    void tableData();
    void changeVel();
    void manageSound(uint64_t realTick);
    void initializePositions();
    void print_usr();
//

static bool startOver = true;


//para inicializar el juego de cero
int runGame(void){
    if(initialize==1){
        startGame();
        return 0;
    }
    initialize=1;
    int aux;
    getScreenWidth(&aux);
    SCREEN_WIDTH=aux;
    getScreenHeight(&aux);
    SCREEN_HEIGHT=aux;    
    time.past=0;
    time.tick = 0;
    // ubico al usuario
    usr_pos[X]=0;
    usr_pos[Y]=0;
    // comienza jugando el jugador 1
    curr_usr=1; 
    lives = LIVESi;
    blocks.left= R_BLOCKS*C_BLOCKS;       
    gameTicks = 0;
    
    info[X]=SCREEN_WIDTH/2;
    info[Y]=SCREEN_HEIGHT-(SCREEN_HEIGHT-BAR_YPOS)/2;
    initializePositions();
    

    /*comienza el juego  */
    startGame();      
    
    return 0;
}

// Inicializo las posiciones de cada pieza
void initializePositions(){
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks.matrix[j][i]= 100;
        }
    }
    
    for (int i = 0; i < R_BLOCKS; i++)
    {
        blocks.matrix[i][1]=PAWN1;
    }
    for (int i = 0; i < R_BLOCKS; i++)
    {
        blocks.matrix[i][6]=PAWN2;
    }
    blocks.matrix[0][0]=ROOK1;
    blocks.matrix[7][0]=ROOK1;
    blocks.matrix[0][7]=ROOK2;
    blocks.matrix[7][7]=ROOK2;
    blocks.matrix[1][0]=KNIGHT1;
    blocks.matrix[6][0]=KNIGHT1;
    blocks.matrix[1][7]=KNIGHT2;
    blocks.matrix[6][7]=KNIGHT2;
    blocks.matrix[2][0]=BISHOP1;
    blocks.matrix[5][0]=BISHOP1;
    blocks.matrix[2][7]=BISHOP2;
    blocks.matrix[5][7]=BISHOP2;
    blocks.matrix[3][0]=QUEEN1;
    blocks.matrix[3][7]=QUEEN2;
    blocks.matrix[4][0]=KING1;
    blocks.matrix[4][7]=KING2;


}



//cuando quiero retomar el juego
int startGame(){
    int aux;
    print_blocks();
    table();
    print_usr();

    bool stopWhile = false;
    goToTerminal = false;
	uint64_t baseTicks = 0,realTicks = 0, previusTick = 0;
    // int re = 0;
    baseTicks = getTicks();
    do{
        realTicks = getTicks() - baseTicks;
        parseKeyboard();

        if(realTicks % REAL_TO_GAME_TICKS == 0 && realTicks != previusTick){
            gameTicks++;
            previusTick = realTicks;
            if((aux = stopKeyPressed()) || lives==0 || blocks.left == 0 ){
                // Condicion de retorno
                stopWhile = true;
            }else
            {
                startGameRec();
            }

        }

    }while(!stopWhile);


    if(aux){ 
        startOver = false;
        return 0;
    }
        
    if(lives == 0  || blocks.left == 0 ){
        int x=finishGame(time.tick / 18);
        initialize=0;
        if(x==0)
            goToTerminal=true;
        else
        {   
            runGame();
        }        
    } 
    return 0;
}

//Esta funcion mueve al usuario y reacciona dependiendo que tecla presiona el usuario
void handleUsrMov(){
    int key = key_pressed();
    int x,y;
    if(key == RIGHT_ARROW){
        if(usr_pos[X] != C_BLOCKS -1){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[X] += 1;                     //muevo al usuario para la derecha
        }
    }
    if(key == LEFT_ARROW){
        if(usr_pos[X] != 0){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[X] -= 1;                     //muevo al usuario para la izquierda
        }
    } 
    if(key == UP_ARROW){
        if(usr_pos[Y] != 0){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[Y] -= 1;                     //muevo al usuario para arriba
        }
    }
    if(key == DOWN_ARROW){
        if(usr_pos[Y] != R_BLOCKS-1){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[Y] += 1;                     //muevo al usuario para abajo
        }
    } 
    if(key == ENTER){
        // si estoy parada sobre una pieza de curr_usr entonces seleccionarla para darle opciones de jugada.
        // activar variable "pieza seleccionada"
    }
    if(key == LEAVE_KEY){
        goToTerminal = true;
    }
}

void print_usr(){
    int usr[2];
    usr[X]=usr_pos[X]*BLOCK_WIDTH;
    usr[Y]=usr_pos[Y]*BLOCK_HEIGHT;
    if(curr_usr == 1){
        print_border(usr, BLOCK_WIDTH ,BLOCK_HEIGHT, BLUE);
    } else {
        print_border(usr, BLOCK_WIDTH ,BLOCK_HEIGHT, RED);        
    }
}

//juega recursivamente
void startGameRec(void){
    tableData(); 
    time.tick ++;
     
    /*MOVIMIENTO DE LA BARRA*/
    handleUsrMov();
    printObjects(block);
}

void printObjects(int * block){
    print_usr(); 
}

void matrixToXY(int * c, int * r){
    *c = (*c * BLOCK_WIDTH) + (BLOCK_WIDTH/2)+ BLOCK_XSEPARATION*(*c+1) ;
    *r = (*r * BLOCK_HEIGHT) + (BLOCK_HEIGHT/2) + BLOCK_YSEPARATION*(*r+1) ;        
}


void makeSquare(int * square, int x, int y){
    square[X] = x;
    square[Y] = y;
    return;
}

void print_blocks(){
    int x;
    int y;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j <R_BLOCKS ; j++){
            print_tile(i,j);
            print_piece(i, j);
        }
    }
}
void print_tile(int i, int j){
    int x=i;
    int y=j;
    matrixToXY(&x, &y);
    if( (i%2 == 0 && j%2 == 0 )|| (i%2 == 1 && j%2==1)){
        print_block( x ,y,WHITE);
                
    }else{
        print_block( x , y,BLACK);
    }
}

void print_piece(int i, int j){
    int x=i;
    int y=j;
    matrixToXY(&x, &y);
    if( blocks.matrix[j][i] == PAWN1){
                print_block( x ,y,AQUA);
            } else if( blocks.matrix[j][i] == PAWN2){
                print_block( x ,y,BLUE);
            } else if( blocks.matrix[j][i] == BISHOP1){
                print_block( x ,y,GREEN);
            } else if( blocks.matrix[j][i] == BISHOP2){
                print_block( x ,y,RED);
            } else if( blocks.matrix[j][i] == ROOK1){
                print_block( x ,y,PURPLE);
            } else if( blocks.matrix[j][i] == ROOK2){
                print_block( x ,y,YELLOW);
            } else if( blocks.matrix[j][i] == KNIGHT1){
                print_block( x ,y,LightBlue);
            } else if( blocks.matrix[j][i] == KNIGHT2){
                print_block( x ,y,LightGreen);
            } else if( blocks.matrix[j][i] == KING1){
                print_block( x ,y,LightPurple);
            } else if( blocks.matrix[j][i] == KING2){
                print_block( x ,y,LightPurple);
            } else if( blocks.matrix[j][i] == QUEEN1){
                print_block( x ,y,LightRed);
            } else if( blocks.matrix[j][i] == QUEEN2){
                print_block( x ,y,LightRed);
            }
            
}

int finishGame(int time_past){
        clearConsole();
        int init;
        getBpp(&init);
        setSize(init*3);
    if(blocks.left == 0){
        printfColorAt("Congratulations you've won!!",RED,BLACK,90,100);
        printfColorAt("It took you %d seconds",RED,BLACK,115,120,time_past);
           
    }else{

        printfColorAt("Better luck next time!",RED,BLACK,90,100);
        printfColorAt("Time: %d seconds",RED,BLACK,115,120,time_past);
    }
        printfColorAt("Press x to restart or q to quit",BLUE,BLACK,50,140,time_past);
        setSize(init);
        char c;
        while((c=readKey())!='x'&& c!='q');
        clearConsole();
        if(c=='x')
         return 1;
    return 0;
}

void print_block(int x,int y,int color){
    int pos[]= {x, y};

    printOnScreen(pos,BLOCK_WIDTH,BLOCK_HEIGHT,color);

}

int stopKeyPressed(){

    return goToTerminal;
}


bool limitInput(char ch){

    if(keyBufferFront-3 > keyBufferBack){
            return ch == KeyBuffer[keyBufferFront-1] && ch == KeyBuffer[keyBufferFront-2] && ch == KeyBuffer[keyBufferFront-3];
    }
    else if(keyBufferBack > keyBufferFront){
        
        if(keyBufferFront -3> 0 ){
            return ch == KeyBuffer[keyBufferFront-1] && ch == KeyBuffer[keyBufferFront-2] && ch == KeyBuffer[keyBufferFront-3];
        }
    }

    return false;
}

void parseKeyboard(){
    if(keyBufferFront + 1 == keyBufferBack )
        keyBufferBack++;
        
    int temp = readKey();
    if((temp == LEFT_ARROW || temp == RIGHT_ARROW || temp == LEAVE_KEY || temp == UP_ARROW || temp == DOWN_ARROW) && !limitInput(temp))
        KeyBuffer[keyBufferFront++ % 200] = temp;

}

int key_pressed(){


    if(keyBufferFront == keyBufferBack)
        return -1;
        
    return KeyBuffer[keyBufferBack++ % 200];


}
void table(){
    // printOnScreen(info,SCREEN_WIDTH,SCREEN_HEIGHT-10000,YELLOW);
    printfColorAt("Blocks left :",YELLOW,BLACK,800,info[1]-100);
    printfColorAt("Lives :",YELLOW,BLACK,800,info[1]-50);
    printfColorAt("Time :",YELLOW,BLACK,800,info[1],time.tick/18);
    tableData();
}

void tableData(){
    if(blocks.left==9)
        printfColorAt(" ",YELLOW,YELLOW,268,info[1]);    

    printfColorAt("%d",YELLOW,BLACK,950,info[1]-100,blocks.left);
    printfColorAt("%d",YELLOW,BLACK,950,info[1]-50,lives);
    printfColorAt("%d",YELLOW,BLACK,850,info[1],time.tick/18);
}

