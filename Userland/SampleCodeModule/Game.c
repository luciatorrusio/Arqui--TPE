#include "./include/Game.h"
#include "../Include/Time.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/deviceInfo.h"
#include <stdbool.h>
#include "./include/Speaker.h"

#define BLOCK_WIDTH                 (SCREEN_HEIGHT/9)
#define BLOCK_XSEPARATION           (0)
#define BLOCK_HEIGHT                (SCREEN_HEIGHT/9)
#define BLOCK_YSEPARATION           (0)

#define REAL_TO_GAME_TICKS          (1)

enum pieces1 {PAWN1=100, BISHOP1, KNIGHT1, ROOK11, ROOK12, QUEEN1, KING1};
enum pieces2 {PAWN2=200, BISHOP2, KNIGHT2, ROOK21, ROOK22, QUEEN2, KING2};
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

#define NO_PIECE                   -1
#define NO_HIGHLIGHT               -1
#define HIGHLIGHT                   1

#define LEFT_ARROW                 'a'
#define RIGHT_ARROW                'd' 
#define UP_ARROW                   'w'
#define DOWN_ARROW                 's'
#define ENTER                      '\n'
#define ROTATE                     'r'
#define ENROQUE                    'e'
#define LEAVE_KEY                  'q'

static int used= false;                     // esta variable es un fix RANCIO, creo que me toma dos veces la funcion print_options_pawn

static int usr_pos[2];
static int curr_usr = 0;
static int piece_selected[2];
static bool select=false;
static bool select_enroque = false;
static int win = 0;

static struct Board board;            
static struct PieceSet set1;              
static struct PieceSet set2;
static struct Board highlightBoard;



static struct Time time;

int block[3]={-1,-1,-1};

static char KeyBuffer[200];
static int keyBufferFront = 0;
static int keyBufferBack = 0;
static bool goToTerminal = false;

static int SCREEN_HEIGHT;
static int SCREEN_WIDTH;
static int info[2];
static int logInfo[20][4];
static int logCount = 0;
static int logIdx = 0;

static uint64_t gameTicks = -1;

uint64_t elapsedTime = 0;
uint64_t turnTicks = 0;

static int initialize= -1;
//DECLARACION DE FUNCIONES
    void printObjects();
    void printLeftover(int * curr_BarPos);
    int key_pressed();
    void parseKeyboard();
    bool limitInput(char ch);
    void table();
    void tableData();
    int curr_set(int x, int y);
    void initializePositions();
    void print_usr();
    void next_highlight();
    int argument(int f,int c, int sum_f, int sum_c, bool is_long);
    void print_piece1(int x, int y, int color);
    void print_piece(int i, int j);
    void print_tile(int i, int j);
    void print_game();
    void matrixToXY(int * c, int * r);
    void print_highlight();
    void highlight(int x, int y);
    void rotate_board(void);
    void rotate_set2(void);
    void rotate_set1(void);
    void rotate_highlight(void);
    int stopKeyPressed(void);
    void print_block(int x,int y,int color);
    void rotate_chess(void);
    void print_options_knight(int x, int y);
    void print_options_rook(int x, int y);
    void print_options_queen(int x,int y);
    void highlight_pawn(int x, int y, int sum_xf, int sum_yf, char change, bool init_pos);
    void print_options_bishop(int x,int y);
    void print_options_king(int x, int y);
    void print_options_pawn(int x, int y);
    void print_tile_options(int x, int y, int piece);
    void clear_highlight(void);
    int opponent_set(int x, int y);
    void nothing_in_middle(int rook);
    void highlight_pawn_diagonal(int x, int y);
    void try_enroque(void);
    void highlight_enroque(int fRook, int cRook);
    void handleUsrMov(void);
    void move_enroque(void);
    void highlight_pawn_forward(int x, int y, int sum_x,  int sum_y, bool init_pos);
    int get_piece(int x, int y);
    int usr_on_own_piece(void);
    void move_enroque2(int yRook, int xRook, int yKing, int xKing, int y2Rook, int x2Rook , int y2King, int x2King, int ROOK, int KING );

    void log();
    void clearLog();
    void updateLog(int usr, int x, int y);
    char * pieceString(int piece);
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
    set1.left = 16;
    set2.left = 16;       
    gameTicks = 0;
    elapsedTime = 0;
    turnTicks = 0;
    // inicializa que nadie gano
    win = 0;
    info[X]=SCREEN_WIDTH;
    info[Y]=SCREEN_HEIGHT-110;
    initializePositions();
    

    /*comienza el juego  */
    startGame();      
    
    return 0;
}

// Inicializo las posiciones de cada pieza
void initializePositions(){
    // inicializo todo como si no hubieran piezas en el tablerp
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            set1.board[j][i]= NO_PIECE;
            set2.board[j][i]= NO_PIECE;
            highlightBoard.board[j][i] = NO_HIGHLIGHT;
        }
    }
    // inicializo de que forma esta el tablero
    board.angle = 0;
    // marco en el tablero donde va a ser negro y donde blanco
    for (int i = 0; i < R_BLOCKS; i++)
    {
        for (int j = 0; j < C_BLOCKS; j++)
        {
            if( (i%2 == 0 && j%2 == 0 )|| (i%2 == 1 && j%2==1)){
                board.board[i][j] = 0;  
            }else{
                board.board[i][j] = 1;
            }
        }
    }

    // Inicializo que ni el rey ni las torres fueron movidas (para el enroque)
    set1.king_moved = false;
    set1.rook1_moved = false;
    set1.rook2_moved = false;
    set2.king_moved = false;
    set2.rook1_moved = false;
    set2.rook2_moved = false;

    // al jugador uno le pongo todos los pawns
    for (int i = 0; i < R_BLOCKS; i++)
    {
        set1.board[i][1]=PAWN1;
    }
    // al jugador 2 le pongo todos los pawns
    for (int i = 0; i < R_BLOCKS; i++)
    {
        set2.board[i][6]=PAWN2;
    }
    
    // pongo las torres al jugador 1
    set1.board[0][0]=ROOK11;
    set1.board[7][0]=ROOK12;
    
    // pongo las torres al jugador 2
    set2.board[0][7]=ROOK21;
    set2.board[7][7]=ROOK22;

    // pongo los caballeros al jugador 1
    set1.board[1][0]=KNIGHT1;
    set1.board[6][0]=KNIGHT1;
    // pongo los caballeros al jugador 2
    set2.board[1][7]=KNIGHT2;
    set2.board[6][7]=KNIGHT2;

    // Pongo los alfiles al jugador 1
    set1.board[2][0]=BISHOP1;
    set1.board[5][0]=BISHOP1;

    // Pongo los alfiles al jugador 2
    set2.board[2][7]=BISHOP2;
    set2.board[5][7]=BISHOP2;
    // Pongo las reinas 
    set1.board[4][0]=QUEEN1;
    set2.board[4][7]=QUEEN2;
    // Pongo los reyes
    set1.board[3][0]=KING1;
    set2.board[3][7]=KING2;
}


//cuando quiero retomar el juego me lleva directo a esta funcion
int startGame(){
    int aux;
    print_game();

    bool stopWhile = false;
    goToTerminal = false;
	uint64_t baseTicks = 0,realTicks = 0, previusTick = 0;
    baseTicks = getTicks();
    do{
        realTicks = getTicks() - baseTicks;
        parseKeyboard();

        if(realTicks % REAL_TO_GAME_TICKS == 0 && realTicks != previusTick){
            gameTicks++;
            previusTick = realTicks;
            if((aux = stopKeyPressed()) ||  win != 0 ){
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
        
    if(win != 0){
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

//juega recursivamente
void startGameRec(void){
    tableData(); 
    time.tick ++;
     
    /*MOVIMIENTO DEL USUARIO*/
    handleUsrMov();
    printObjects();
    turnTicks=(time.tick/18)-elapsedTime;
    if (turnTicks >= 20){
        if(curr_usr == 1){
            win = 2;
        }else {
            win = 1;
        }
        return;
    }
}

//Esta funcion mueve al usuario y reacciona dependiendo que tecla presiona el usuario
void handleUsrMov(){
    int key = key_pressed();

    if(select == true){
        if(key == RIGHT_ARROW){
            next_highlight();                                   //muevo al usuario a la proxima opcion
        }
        else if(key == LEFT_ARROW){
            next_highlight();      // hacerlo si hay tiempo         
        }else if(key == ROTATE){
            rotate_chess();               
        }else if(key == ENROQUE && select_enroque == true){
            select = false;
            select_enroque = false; 
            clear_highlight();             
        } 
        else if(key == ENTER){
            select = false;
            used = false;
            clear_highlight();
            //time.tick/18 cunatos segundo en el juego
            //segundos en juego el jugador especifico en el turno
            elapsedTime+=turnTicks;

            if(!usr_on_own_piece())
                updateLog(curr_usr,usr_pos[X],usr_pos[Y]);

            if(select_enroque == true){
                move_enroque();
                select_enroque = false;
                if(curr_usr == 1){
                    curr_usr = 2;
                }else {
                    curr_usr = 1;
                }
            } else if(curr_usr == 1){
                //aca se come la pieza del otro  eficientizar
                if(set2.board[usr_pos[Y]][usr_pos[X]] != NO_PIECE){
                    if(get_piece(usr_pos[X], usr_pos[Y])== KING2){
                        win = 1;
                        return;
                    }
                    set2.board[usr_pos[Y]][usr_pos[X]] = NO_PIECE;
                    set1.board[usr_pos[Y]][usr_pos[X]] = get_piece(piece_selected[X], piece_selected[Y]);
                    set1.board[piece_selected[Y]][piece_selected[X]]= NO_PIECE;
                    print_tile(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    print_tile(piece_selected[X],piece_selected[Y]);
                    print_piece( piece_selected[X], piece_selected[Y]);
                    set2.left--;
                    curr_usr = 2;
                    
                }// aca se mueve a un lugar sin nadie 
                else if(set1.board[usr_pos[Y]][usr_pos[X]] == NO_PIECE){
                    set1.board[usr_pos[Y]][usr_pos[X]] = get_piece(piece_selected[X], piece_selected[Y]);
                    print_tile(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    set1.board[piece_selected[Y]][piece_selected[X]]= NO_PIECE;
                    print_tile(piece_selected[X],piece_selected[Y]);
                    print_piece( piece_selected[X], piece_selected[Y]);
                    curr_usr = 2;
                }
            }
            else if(curr_usr == 2){
                // aca come a la ficha del otro
                if(set1.board[usr_pos[Y]][usr_pos[X]] != NO_PIECE){
                    if(get_piece(usr_pos[X], usr_pos[Y])== KING1){
                        win = 2;
                        return;
                    }
                    set1.board[usr_pos[Y]][usr_pos[X]] = NO_PIECE;
                    set2.board[usr_pos[Y]][usr_pos[X]] = get_piece(piece_selected[X], piece_selected[Y]);
                    set2.board[piece_selected[Y]][piece_selected[X]]= NO_PIECE;
                    print_tile(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    print_tile(piece_selected[X],piece_selected[Y]);
                    print_piece( piece_selected[X], piece_selected[Y]);
                    set1.left--;
                    curr_usr = 1;
                    
                } // aca mueve su ficha a un espacio vacio
                else if(set2.board[usr_pos[Y]][usr_pos[X]] == NO_PIECE){
                    set2.board[usr_pos[Y]][usr_pos[X]] = get_piece(piece_selected[X], piece_selected[Y]);
                    print_tile(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    set2.board[piece_selected[Y]][piece_selected[X]]= NO_PIECE;
                    print_tile(piece_selected[X],piece_selected[Y]);
                    print_piece( piece_selected[X], piece_selected[Y]);
                    curr_usr = 1;
                }
            }
        }
    }
    else if(key == RIGHT_ARROW){
        if(usr_pos[X] != C_BLOCKS -1){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[X] += 1;                     //muevo al usuario para la derecha
        }
    } else if(key == LEFT_ARROW){
        if(usr_pos[X] != 0){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[X] -= 1;                     //muevo al usuario para la izquierda
        }
    } else if(key == UP_ARROW){
        if(usr_pos[Y] != 0){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[Y] -= 1;                     //muevo al usuario para arriba
        }
    } else if(key == DOWN_ARROW){
        if(usr_pos[Y] != R_BLOCKS-1){
            print_tile(usr_pos[X],usr_pos[Y]);
            print_piece( usr_pos[X], usr_pos[Y]);
            usr_pos[Y] += 1;                     //muevo al usuario para abajo
        }
    }else if(key == ROTATE){
        rotate_chess();               
    }
    else if(key == ENROQUE){
        try_enroque();
        
    }
    else if(key == ENTER){ 
        if(usr_on_own_piece()){
            select = true;
            piece_selected[X]=usr_pos[X];
            piece_selected[Y]= usr_pos[Y];
            int piece = get_piece(usr_pos[X], usr_pos[Y]);
            print_tile_options(usr_pos[X],usr_pos[Y], piece);
        }
        // si estoy parada sobre una pieza de curr_usr entonces seleccionarla para darle opciones de jugada.
        // activar variable "pieza seleccionada"
    } else if(key == LEAVE_KEY){
        goToTerminal = true;
    }
}

// Esta funcion se fija si puede hacer enroque y highlightea con las torres que se puede hacer
void try_enroque(){
    if(curr_usr == 1){
        if(set1.king_moved == false){
            if(!set1.rook1_moved){
                nothing_in_middle(ROOK11);
            } 
            if(!set1.rook2_moved){
                nothing_in_middle(ROOK12);
            }
        }    
    } 
    else if(curr_usr == 2){
        if(set2.king_moved == false){
            if(set2.rook1_moved == false){
                nothing_in_middle(ROOK21);
            }
            if(set2.rook2_moved == false){
                nothing_in_middle(ROOK22);
            }
        
        }
    } 
}

// Esta funcion hace el movimiento del enroque dado de donde a donde va el king de donde a donde va el rook y sus nombres especificos
void move_enroque2(int yRook, int xRook, int yKing, int xKing, int y2Rook, int x2Rook , int y2King, int x2King, int ROOK, int KING ){
    if(curr_usr == 1){
        set1.board[yRook][xRook] = NO_PIECE;
        set1.board[yKing][xKing] = NO_PIECE;
        set1.board[y2Rook][x2Rook] = ROOK;
        set1.board[y2King][x2King]= KING;
    }
    else {
        set2.board[yRook][xRook] = NO_PIECE;
        set2.board[yKing][xKing] = NO_PIECE;
        set2.board[y2Rook][x2Rook] = ROOK;
        set2.board[y2King][x2King]= KING;
    }
    print_tile(x2Rook,y2Rook);
    print_piece(x2Rook,y2Rook);
    print_tile(x2King,y2King);
    print_piece(x2King,y2King);
    print_tile(xRook,yRook);
    print_piece(xRook,yRook);
    print_tile(xKing,yKing);
    print_piece(x2King,y2King);
}

// Esta funcioin le da el contexto de las posiciones para poder moverse COMPLETAR   
void move_enroque(){
    //bien posiciones
    int rook = get_piece(usr_pos[X], usr_pos[Y]);
    if(rook == ROOK11){
        if(board.angle == 0){
            move_enroque2(0,0,3,0,2,0,1,0, ROOK11, KING1);
            set1.rook1_moved = true; 
            set1.king_moved = true;     
        }
        else if(board.angle == 1){
            move_enroque2(0,7,0,4,0,5,0,6, ROOK11, KING1);
            set1.rook1_moved = true;  
            set1.king_moved = true;   
        }
        else if(board.angle == 2){
            move_enroque2(7,7,4,7,5,7,6,7, ROOK11, KING1);
            set1.rook1_moved = true; 
            set1.king_moved = true;  
        }
        else if(board.angle == 3){
            move_enroque2(7,0,7,3,7,2,7,1, ROOK11, KING1);
            set1.rook1_moved = true;
            set1.king_moved = true;   
        }
    }
    else if(rook == ROOK22){
        if(board.angle == 2){
            move_enroque2(0,0,4,0,3,0,2,0, ROOK22, KING2); 
            set2.rook2_moved = true;
            set2.king_moved = true;    
        }
        else if(board.angle == 3){
            move_enroque2(0,7,0,3,0,4,0,5, ROOK22, KING2);
            set2.rook2_moved = true;  
            set2.king_moved = true; 
        }
        else if(board.angle == 0){
            move_enroque2(7,7,3,7,4,7,5,7, ROOK22, KING2);
            set2.rook2_moved = true;   
            set2.king_moved = true;
        }
        else if(board.angle == 1){
            move_enroque2(7,0,7,4,7,3,7,2, ROOK22, KING2);
            set2.rook2_moved = true; 
            set2.king_moved = true;  
        }
    }
    else if(rook == ROOK21){
        if(board.angle == 3){
            move_enroque2(0,0,0,4,0,3,0,2, ROOK21, KING2);
            set2.rook1_moved = true; 
            set2.king_moved = true;     
        }
        else if(board.angle == 0){
            move_enroque2(0,7,3,7,2,7,1,7, ROOK21, KING2);
            set2.rook1_moved = true; 
            set2.king_moved = true;
        }
        else if(board.angle == 1){
            move_enroque2(7,7,7,4,7,5,7,6, ROOK21, KING2);
            set2.rook1_moved = true; 
            set2.king_moved = true;
        }
        else if(board.angle == 2){
            move_enroque2(7,0,4,0,5,0,6,0, ROOK21, KING2);
            set2.rook1_moved = true; 
            set2.king_moved = true;
        }
    }
    else if(rook == ROOK12){
        if(board.angle == 1){
            move_enroque2(0,0,0,4,0,3,0,2, ROOK12, KING1); 
            set1.rook2_moved = true; 
            set1.king_moved = true;   
        }
        else if(board.angle == 2){
            move_enroque2(0,7,4,7,3,7,2,7, ROOK12, KING1);
            set1.rook2_moved = true; 
            set1.king_moved = true; 
        }
        else if(board.angle == 3){
            move_enroque2(7,7,7,3,7,4,7,5, ROOK12, KING1);
            set1.rook2_moved = true; 
            set1.king_moved = true; 
        }
        else if(board.angle == 0){
            move_enroque2(7,0,3,0,4,0,5,0, ROOK12, KING1);
            set1.rook2_moved = true; 
            set1.king_moved = true; 
        }
    }
    
    
}

void highlight_enroque(int fRook, int cRook){
    highlightBoard.board[fRook][cRook] = HIGHLIGHT;
    print_tile(usr_pos[X], usr_pos[Y]);
    print_highlight();
    print_piece(usr_pos[X], usr_pos[Y]);
    
    usr_pos[X] = cRook;
    usr_pos[Y] = fRook;
    select_enroque = true;
    select = true;
}

void nothing_in_middle(int rook){
    if(rook == ROOK11){
        if(board.angle == 0 && argument(0,0, 1, 0 , false)){
            highlight_enroque(0,0);
        }
        else if(board.angle == 1 && argument(0,7, 0, -1 , false)==true ){
            highlight_enroque(0,7);
        }else if(board.angle == 2 && argument(7,7, -1, 0 , false)==true){
            highlight_enroque(7,7);
        }else if(board.angle == 3 && argument(7,0, 0, 1 , false)==true){
            highlight_enroque(7,0);
        }
    }
    else if(rook == ROOK22){
        if(board.angle == 2 && argument(0,0, 1, 0 , true)==true){
            highlight_enroque(0,0);
        }else if(board.angle == 3 && argument(0,7, 0, -1 , true)==true ){
            highlight_enroque(0,7);
        }else 
        if((board.angle == 0) && (argument(7,7, -1, 0 , true)==true)){
            highlight_enroque(7,7);
        }
        else if(board.angle == 1 && argument(7,0, 0, 1 , true)==true){
            highlight_enroque(7,0);
        }
    }
    else if(rook == ROOK12){
        if(board.angle == 1 && argument(0,0, 0, -1 , true)==true){
            highlight_enroque(0,0);
        }else if(board.angle == 2 && argument(0,7, 1, 0 , true)==true ){
            highlight_enroque(0,7);
        }else if(board.angle == 3 && argument(7,7, 0, -1, true)==true){
            highlight_enroque(7,7);
        }else if(board.angle == 0 && argument(7,0, -1, 0 , true)==true){
            highlight_enroque(7,0);
        }
    }
    else if(rook == ROOK21){
        if(board.angle == 3 && (argument(0,0, 0, 1, false)==true)){
            highlight_enroque(0,0);
        }else if(board.angle == 0 && (argument(0,7, 1, 0 , false)==true) ){
            highlight_enroque(0,7);
        }else if(board.angle == 1 && (argument(7,7, 0, -1, false)==true)){
            highlight_enroque(7,7);
        }else if(board.angle == 2 && (argument(7,0, -1, 0 , false)==true)){
            highlight_enroque(7,0);
        }
    }
    
}

int argument(int f,int c, int sum_f, int sum_c, bool is_long){
    f+=sum_f;
    c+=sum_c;
    if(curr_set(c, f) == NO_PIECE && opponent_set(c, f)==NO_PIECE){
        f+=sum_f;
        c+=sum_c;
        if(curr_set(c, f)== NO_PIECE  && opponent_set(c, f)==NO_PIECE){
            f+=sum_f;
            c+=sum_c;
            if((is_long == true) && (curr_set(c, f)== NO_PIECE)  && (opponent_set(c, f)==NO_PIECE)){
                return true;
            }else if(!is_long){
                return true;

            }
        }
    } 
                
    return false; 
       
}

// pone la matriz de highlight todas en NO_HIGHLIGHT
void clear_highlight(){
    for (int j = 0; j < R_BLOCKS ; j++)
    {
        for (int i = 0; i < C_BLOCKS; i++)
        {
            if(highlightBoard.board[j][i] == HIGHLIGHT){
                highlightBoard.board[j][i]= NO_HIGHLIGHT;
                print_tile(i, j);
                print_piece(i,j);
            }
                
        }
        
    }
    
}

// mueve al usuario a la proxima opcion de moverse
void next_highlight(){
    int x;
    // primero se fija entre los proximos en el board
    for ( int i = usr_pos[Y]; i < R_BLOCKS; i++)
    {
        if(x==0){
            for( int j = usr_pos[X]+1; j<C_BLOCKS; j++){
                if(highlightBoard.board[i][j] == HIGHLIGHT){
                    print_tile(usr_pos[X],usr_pos[Y]);
                    if(highlightBoard.board[usr_pos[Y]][usr_pos[X]] == HIGHLIGHT)
                        highlight(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    usr_pos[X]=j;
                    usr_pos[Y]=i;
                    return;
                }
            }
            x++;
        }else {
            for( int j = 0; j<C_BLOCKS; j++){
                if(highlightBoard.board[i][j] == HIGHLIGHT){
                    print_tile(usr_pos[X],usr_pos[Y]);
                    if(highlightBoard.board[usr_pos[Y]][usr_pos[X]] == HIGHLIGHT)
                        highlight(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    usr_pos[X]=j;
                    usr_pos[Y]=i;
                    return;
                }
            }
        }
        
    }
    // si no encuentra se fija entre los anteriores a el
    for ( int i = 0; i < usr_pos[Y]+1; i++)
    {
        if(i == usr_pos[Y]){
            for( int j = 0; j<usr_pos[X]; j++){
                if(highlightBoard.board[i][j] == HIGHLIGHT){
                    print_tile(usr_pos[X],usr_pos[Y]);
                    highlight(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    usr_pos[X]=j;
                    usr_pos[Y]=i;
                    return;
                }
            }
        } else {
            for( int j = 0; j<C_BLOCKS; j++){
                if(highlightBoard.board[i][j] == HIGHLIGHT){
                    print_tile(usr_pos[X],usr_pos[Y]);
                    highlight(usr_pos[X],usr_pos[Y]);
                    print_piece( usr_pos[X], usr_pos[Y]);
                    usr_pos[X]=j;
                    usr_pos[Y]=i;
                    return;
                }
            }
        }
        
    }
    
}

// devuelve si el user esta situado en su propia pieza
int usr_on_own_piece(){
    if(curr_usr == 1 && set1.board[usr_pos[Y]][usr_pos[X]] != NO_PIECE){
        return true;
    } else if( curr_usr == 2 && set2.board[usr_pos[Y]][usr_pos[X]] != NO_PIECE)
    {
        return true;
    }
    return false;
}

// retorna la pieza en el lugar especificado
int get_piece(int x, int y){
    if(set1.board[y][x] != NO_PIECE){
        return set1.board[y][x];
    } else if (set2.board[y][x] != NO_PIECE) {
        return set2.board[y][x];
    }
    return NO_PIECE;
    
}

// me highlitea en el tablero los lugares donde me puedo mover (incluyendo el lugar donde estoy parado)
void print_tile_options(int x, int y, int piece){
    switch (piece)
    {
    case PAWN1:
    case PAWN2:
        print_options_pawn(x,y);
        break;
    case KING1:
    case KING2:
        print_options_king(x,y);
        break;
    case KNIGHT1:
    case KNIGHT2:
        print_options_knight(x,y);
        break;
    case BISHOP1:
    case BISHOP2:
        print_options_bishop(x,y);
        break;
    case QUEEN1:
    case QUEEN2:
        print_options_queen(x,y);
        break;
    case ROOK11:
    case ROOK12:
    case ROOK21:
    case ROOK22:
        print_options_rook(x,y);
        break;
        
    
    default:
        break;
    }
}

void highlight_pawn_forward(int x, int y, int sum_x,  int sum_y, bool init_pos){
    if(curr_set(x+sum_x, y+sum_y)== NO_PIECE && opponent_set(x+sum_x, y+sum_y) == NO_PIECE && x+sum_x<C_BLOCKS && x+sum_x>=0 && y+sum_y<R_BLOCKS && y+sum_y>=0 ){
        highlight(x+sum_x, y+sum_y);
        highlightBoard.board[y+sum_y][x+sum_x] = HIGHLIGHT;
        if(init_pos && set1.board[y+sum_y+sum_y][x+sum_x+sum_x] == NO_PIECE && set2.board[y+sum_y+sum_y][x+sum_x+sum_x] == NO_PIECE)
        {
            highlight(x+sum_x+sum_x, y+sum_y+sum_y);
            highlightBoard.board[y+sum_y+sum_y][x+sum_x+sum_x] = HIGHLIGHT;
        }
    }
}
void highlight_pawn_diagonal(int x, int y){
    if(curr_set(x, y) == NO_PIECE && opponent_set(x,y)!=NO_PIECE && x<C_BLOCKS && y>=0 && x>=0 && y<R_BLOCKS){
        if(used == false){
            used == true;
            highlight(x, y);
            highlightBoard.board[y][x] = HIGHLIGHT;
        } 
    }  
}
void highlight_pawn(int x, int y, int sum_xf, int sum_yf, char change, bool init_pos){
    highlight_pawn_forward(x, y, sum_xf,  sum_yf, init_pos);
    if(change == 'y'){
        highlight_pawn_diagonal(x+sum_xf, y-1);
        highlight_pawn_diagonal(x+sum_xf, y+1);
    }
    else if(change == 'x'){
        highlight_pawn_diagonal(x-1, y+sum_xf);
        highlight_pawn_diagonal(x+1, y+sum_yf);
    }
    
}

// resalta en el tablero donde se puede mover un pawn en especifico
void print_options_pawn(int x, int y){
    highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    if (curr_usr == 1 && board.angle == 0){
        highlight_pawn(x,y,1,0,'y',x==1);      
    }
    else if (curr_usr == 2 && board.angle == 0){
        highlight_pawn(x,y,-1,0,'y',x==C_BLOCKS-2);    
    }
    else if (curr_usr == 1 && board.angle == 1){
        highlight_pawn(x,y,0,1,'x',y==1);
    } 
    else if (curr_usr == 2 && board.angle == 1){  
        highlight_pawn(x,y,0,-1,'x',y==R_BLOCKS-2);     
    }
    else if (curr_usr == 2 && board.angle == 2){
        highlight_pawn(x,y,1,0,'y',x==1);      
    }
    else if (curr_usr == 1 && board.angle == 2){
        highlight_pawn(x,y,-1,0,'y',x==C_BLOCKS-2);    
    }
    else if (curr_usr == 2 && board.angle == 3){
        highlight_pawn(x,y,0,1,'x',y==1);
    } 
    else if (curr_usr == 1 && board.angle == 3){  
        highlight_pawn(x,y,0,-1,'x',y==R_BLOCKS-2);     
    }
}

void print_options_king(int x, int y){
    highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    if(curr_set(x+1, y) == NO_PIECE && x<C_BLOCKS-1){
        highlight(x+1, y);
        highlightBoard.board[y][x+1] = HIGHLIGHT;
    }
    if(curr_set(x-1, y) == NO_PIECE && x>0 ){
        highlight(x-1, y);
        highlightBoard.board[y][x-1] = HIGHLIGHT;
    }
    if(curr_set(x, y-1) == NO_PIECE &&  y>0){
        highlight(x, y-1);
        highlightBoard.board[y-1][x] = HIGHLIGHT;
    }
    if(curr_set(x, y+1) == NO_PIECE && y<R_BLOCKS-1){
        highlight(x, y+1);
        highlightBoard.board[y+1][x] = HIGHLIGHT;
    }
    if(curr_set(x-1, y+1) == NO_PIECE && x>0 && y<R_BLOCKS-1){
        highlight(x-1, y-1);
        highlightBoard.board[y-1][x-1] = HIGHLIGHT;
    }
    if(curr_set(x+1, y+1) == NO_PIECE && x<C_BLOCKS-1 && y<R_BLOCKS-1){
        highlight(x+1, y+1);
        highlightBoard.board[y+1][x+1] = HIGHLIGHT;
    }
    if(curr_set(x+1, y-1) == NO_PIECE && x<C_BLOCKS-1 &&  y>0){
        highlight(x+1, y-1);
        highlightBoard.board[y-1][x+1] = HIGHLIGHT;
    }
    if(curr_set(x-1, y-1) == NO_PIECE && x>0 && y>0){
        highlight(x-1, y-1);
        highlightBoard.board[y-1][x-1] = HIGHLIGHT;
    }
}

void print_options_bishop(int x,int y){
    highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    int i=x+1;
    int j=y-1;
    int stop=false;
    // se extiende para arriba y la derecha
    while( i<C_BLOCKS && j>=0 && stop==false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        
        i++;
        j--;
    }
    i=x-1;
    j=y-1;
    stop = false;
    // se extiende para arriba y la izquierda
    while(i>=0 && j>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE ){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
        j--;
    }
    i=x-1;
    j=y+1;
    stop = false;
    // se extiende para abajo y la izquierda
    while(i>=0 && j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE ){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
        j++;
    }
    i=x+1;
    j=y+1;
    stop = false;
    // se extiende para abajo y la derecha
    while(i<C_BLOCKS && j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i++;
        j++;
    }
}

void print_options_queen(int x,int y){
    highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    int i=x+1;
    int j=y-1;
    int stop=false;
    // se extiende para arriba y la derecha
    while( i<C_BLOCKS && j>=0 && stop==false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        
        i++;
        j--;
    }
    i=x-1;
    j=y-1;
    stop = false;
    // se extiende para arriba y la izquierda
    while(i>=0 && j>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE ){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
        j--;
    }
    i=x-1;
    j=y+1;
    stop = false;
    // se extiende para abajo y la izquierda
    while(i>=0 && j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE ){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
        j++;
    }
    i=x+1;
    j=y+1;
    stop = false;
    // se extiende para abajo y la derecha
    while(i<C_BLOCKS && j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i++;
        j++;
    }
    i=x+1;
    j=y;
    stop = false;
    // se extiende para la derecha
    while(i<C_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i++;
    }
    i=x-1;
    j=y;
    stop = false;
    // se extiende para la izquierda
    while(i>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
    }
    i=x;
    j=y+1;
    stop = false;
    // se extiende para abajo 
    while( j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        j++;
    }
    i=x;
    j=y-1;
    stop = false;
    // se extiende para arriba
    while( j>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        j--;
    }
}

void print_options_rook(int x, int y){
  highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    int i=x+1;
    int j=y;
    int stop=false;
    // se extiende para la derecha
    while(i<C_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i++;
    }
    i=x-1;
    j=y;
    stop = false;
    // se extiende para la izquierda
    while(i>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        i--;
    }
    i=x;
    j=y+1;
    stop = false;
    // se extiende para abajo 
    while( j<R_BLOCKS && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        j++;
    }
    i=x;
    j=y-1;
    stop = false;
    // se extiende para arriba
    while( j>=0 && stop == false){
        if(curr_set(i,j) != NO_PIECE){
            stop=true;
        } else if(opponent_set(i, j) != NO_PIECE){
            stop=true;
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        } else {
            highlight(i, j);
            highlightBoard.board[j][i] = HIGHLIGHT;
        }
        j--;
    }
      
}

// resalta en el tablero donde se puede mover un peon en especifico
void print_options_knight(int x, int y){
    highlightBoard.board[y][x] = HIGHLIGHT;
    highlight(x, y);
    if(curr_set(x+2, y+1) == NO_PIECE && y+1<R_BLOCKS && x+2<C_BLOCKS){
        highlight(x+2, y+1);
        highlightBoard.board[y+1][x+2] = HIGHLIGHT;
    }
    if(curr_set(x+2, y-1) == NO_PIECE && y-1>=0  && x+2<C_BLOCKS){
        highlight(x+2, y-1);
        highlightBoard.board[y-1][x+2] = HIGHLIGHT;
    }
    if(curr_set(x-2, y+1) == NO_PIECE && y+1<R_BLOCKS && x-2>=0){
        highlight(x-2, y+1);
        highlightBoard.board[y+1][x-2] = HIGHLIGHT;
    }
    if(curr_set(x-2, y-1) == NO_PIECE && y-1>=0  && x-2>=0){
        highlight(x-2, y-1);
        highlightBoard.board[y-1][x-2] = HIGHLIGHT;
    }
    if(curr_set(x+1, y-2) == NO_PIECE && x+1<C_BLOCKS && y-2>=0){
        highlight(x+1, y-2);
        highlightBoard.board[y-2][x+1] = HIGHLIGHT;
    }
    if(curr_set(x-1, y-2) == NO_PIECE && y-2>=0 && x-1>=0){
        highlight(x-1, y-2);
        highlightBoard.board[y-2][x-1] = HIGHLIGHT;
    }
    if(curr_set(x-1, y+2) == NO_PIECE && x-1>=0 && y+2<R_BLOCKS){
        highlight(x-1, y+2);
        highlightBoard.board[y+2][x-1] = HIGHLIGHT;
    }
    if(curr_set(x+1, y+2) == NO_PIECE && x+1<C_BLOCKS && y+2<R_BLOCKS){
        highlight(x+1, y+2);
        highlightBoard.board[y+2][x+1] = HIGHLIGHT;
    }
    
}

// devuelve la pieza del jugador en juego en el lugar especifico
int curr_set(int x, int y){
    if (curr_usr == 1){
        return set1.board[y][x];
    }
    return set2.board[y][x];
}

// devuelve la pieza del jugador que no esta en juego en el lugar especifico
int opponent_set(int x, int y){
    if (curr_usr == 1){
        return set2.board[y][x];
    }
    return set1.board[y][x];
}

void rotate_chess(){
    if(board.angle == 3){
        board.angle = 0;
    }else {
        board.angle++;
    }
    rotate_highlight();
    rotate_set1();
    rotate_set2();
    rotate_board();
    print_game();
}
void rotate_highlight(){
    int k=0;
    int piece;
    for (int j = 0 ; j<R_BLOCKS ; j++){
        for(int i=0+k; i<C_BLOCKS ; i++){
            piece = highlightBoard.board[j][i];
            highlightBoard.board[j][i] = highlightBoard.board[i][j];
            highlightBoard.board[i][j] =piece;
        }
        k++;
    }
    for (int j = 0 ; j<R_BLOCKS; j++){
        for(int i= 0; i<(C_BLOCKS/2); i++){
            piece = highlightBoard.board[j][i];
            highlightBoard.board[j][i] = highlightBoard.board[j][R_BLOCKS-1-i];
            highlightBoard.board[j][R_BLOCKS-1-i] = piece;
        }
    }
    
}
void rotate_set1(){
    int k=0;
    int piece;
    for (int j = 0 ; j<R_BLOCKS ; j++){
        for(int i=0+k; i<C_BLOCKS ; i++){
            piece = set1.board[j][i];
            set1.board[j][i] = set1.board[i][j];
            set1.board[i][j] =piece;
        }
        k++;
    }
    for (int j = 0 ; j<R_BLOCKS ; j++){
        for(int i= 0; i<(C_BLOCKS/2 ); i++){
            piece = set1.board[j][i];
            set1.board[j][i] = set1.board[j][R_BLOCKS-1-i];
            set1.board[j][R_BLOCKS-1-i] =piece;
        }
    }
}
void rotate_set2(){
    int k=0;
    int piece;
    // primero hacemos la transpuesta
    for (int j = 0 ; j<R_BLOCKS ; j++){
        for(int i=0+k; i<C_BLOCKS ; i++){
            piece = set2.board[j][i];
            set2.board[j][i] = set2.board[i][j];
            set2.board[i][j] =piece;
        }
        k++;
    }
    // despues espejo sobre el eje x
    for (int j = 0 ; j<R_BLOCKS; j++){
        for(int i=0; i<(C_BLOCKS/2 ); i++){
            piece = set2.board[j][i];
            set2.board[j][i] = set2.board[j][R_BLOCKS-1-i];
            set2.board[j][R_BLOCKS-1-i] = piece;
        }
    }
}
void rotate_board(){
    int k=0;
    int piece;
    // primero hacemos la transpuesta
    for (int j = 0 ; j<R_BLOCKS; j++){
        for(int i=0+k; i<C_BLOCKS ; i++){
            piece = board.board[j][i];
            board.board[j][i] = board.board[i][j];
            board.board[i][j] = piece;
        }
        k++;
    }
    //despues espejo sobre el eje x
    for (int j = 0 ; j<R_BLOCKS; j++){
        for(int i=0; i<(C_BLOCKS/2) ; i++){
            piece = board.board[j][i];
            board.board[j][i] = board.board[j][R_BLOCKS-1-i];
            board.board[j][R_BLOCKS-1-i] = piece;
        }
    }
}


//Prints a border that indicates where the user is standing
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

//Le paso la posicion en la matriz, no de la pantalla
void highlight(int x, int y){
    int pos[2];
    pos[X]=x*BLOCK_WIDTH;
    pos[Y]=y*BLOCK_HEIGHT;
    highlightTile(pos, BLOCK_WIDTH, BLOCK_HEIGHT, YELLOW);
}

void print_highlight(){
    int pos[2];
    for(int j=0; j<C_BLOCKS; j++){
        for (int i = 0; i < R_BLOCKS; i++)
        {
            if(highlightBoard.board[j][i] == HIGHLIGHT ){
                pos[X]=i*BLOCK_WIDTH;
                pos[Y]=j*BLOCK_HEIGHT;
                highlightTile(pos, BLOCK_WIDTH, BLOCK_HEIGHT, YELLOW);
            }
        }
        

    }
}


void printObjects(){
    print_usr(); 
}

void matrixToXY(int * c, int * r){
    *c = (*c * BLOCK_WIDTH) + (BLOCK_WIDTH/2)+ BLOCK_XSEPARATION*(*c+1) ;
    *r = (*r * BLOCK_HEIGHT) + (BLOCK_HEIGHT/2) + BLOCK_YSEPARATION*(*r+1) ;        
}


// printea todo retomando como estaba antes
void print_game(){
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j <R_BLOCKS ; j++){
            print_tile(i,j);
            print_piece(i, j);
        }
    }
    print_highlight();
    table();
    log();
    print_usr();
}

void print_tile(int i, int j){
    int x=i;
    int y=j;
    matrixToXY(&x, &y);
    if( board.board[j][i] == 1){
        print_block( x ,y,WHITE);
                
    }else{
        print_block( x , y,BLACK);
    }
}

void print_piece(int i, int j){
    int x=i;
    int y=j;
    matrixToXY(&x, &y);
    int pos[2] = {x, y};
    if( set1.board[j][i] == PAWN1){
        printPiece(pos,P_PAWN,BLUE);
        // print_piece1( x ,y,AQUA);
    } else if( set2.board[j][i] == PAWN2){
        printPiece(pos,P_PAWN,RED);
        // print_piece1( x ,y,BLUE);
    } else if( set1.board[j][i] == BISHOP1){
        printPiece(pos,P_BISHOP,BLUE);
        // print_piece1( x ,y,GREEN);
    } else if( set2.board[j][i] == BISHOP2){
        printPiece(pos,P_BISHOP,RED);
        // print_piece1( x ,y,RED);
    } else if( set1.board[j][i] == ROOK11 || set1.board[j][i] == ROOK12 ){
        printPiece(pos,P_ROOK,BLUE);
        // print_piece1( x ,y,PURPLE);
    } else if( set2.board[j][i] == ROOK22 || set2.board[j][i] == ROOK21){
        printPiece(pos,P_ROOK,RED);
        // print_piece1( x ,y,YELLOW);
    } else if( set1.board[j][i] == KNIGHT1){
        printPiece(pos,P_KNIGHT,BLUE);
        // print_piece1( x ,y,LightBlue);
    } else if( set2.board[j][i] == KNIGHT2){
        printPiece(pos,P_KNIGHT,RED);
        // print_piece1( x ,y,LightGreen);
    } else if( set1.board[j][i] == KING1){
        printPiece(pos,P_KING,BLUE);
        // print_piece1( x ,y,LightPurple);
    } else if( set2.board[j][i] == KING2){
        printPiece(pos,P_KING,RED);
        // print_piece1( x ,y,LightPurple);
    } else if( set1.board[j][i] == QUEEN1){
        printPiece(pos,P_QUEEN,BLUE);
        // print_piece1( x ,y,LightRed);
    } else if( set2.board[j][i] == QUEEN2){
        printPiece(pos,P_QUEEN,RED);
        // print_piece1( x ,y,LightRed);
}
            
}

int finishGame(int time_past){
        clearConsole();
        clearLog();
        int init;
        getBpp(&init);
        setSize(init*3);
        printfColorAt("Congratulations player %d won!!",RED,BLACK,40,100, win);
        printfColorAt("It took you %d seconds",RED,BLACK,40,120,time_past);
        printfColorAt("Press x to restart or q to quit",BLUE,BLACK,40,140,time_past);
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

void print_piece1(int x, int y, int color){
    int pos[]= {x, y};

    printOnScreen(pos,BLOCK_WIDTH/2,BLOCK_HEIGHT/2,color);
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
    if((temp == LEFT_ARROW || temp == RIGHT_ARROW || temp == LEAVE_KEY || temp == UP_ARROW || temp == DOWN_ARROW || temp == ENTER ||temp == ROTATE ||temp == ENROQUE) && !limitInput(temp))
        KeyBuffer[keyBufferFront++ % 200] = temp;

}

int key_pressed(){


    if(keyBufferFront == keyBufferBack)
        return -1;
        
    return KeyBuffer[keyBufferBack++ % 200];


}

void log() {
    printfColorAt("-- LOG -------------------------------",WHITE,BLACK,700,15);
    if(logCount!=0) {
        int idx = 0;
        for(int i=0; i<logCount; i++, idx++) {
            printfColorAt("Player %d moves to row %d, column %d", logInfo[i][0]==1 ? BLUE:RED,BLACK,700,20*(2+idx),logInfo[i][0],logInfo[i][2],logInfo[i][1]);
            if(logInfo[i][3]!=0) {
                idx++;
                printfColorAt("Player %d captures %s",logInfo[i][0]==1 ? BLUE:RED,BLACK,700,20*(2+idx),logInfo[i][0],pieceString(logInfo[i][3]));
            }
        }
    }
    printfColorAt("--------------------------------------",WHITE,BLACK,700,420);
}

void clearLog() {
    for(int i=0; i<logCount; i++) {
        for(int j=0; j<4; j++) {
            logInfo[i][j] = 0;
        }
    }
    logCount = 0;
    logIdx = 0;
}

char * pieceString(int piece) {
    switch (piece) {
        case PAWN1:
        case PAWN2:
            return "pawn";
            break;
        case KING1:
        case KING2:
            return "king";
            break;
        case KNIGHT1:
        case KNIGHT2:
            return "knight";
            break;
        case BISHOP1:
        case BISHOP2:
            return "bishop";
            break;
        case QUEEN1:
        case QUEEN2:
            return "queen";
            break;
        case ROOK12:
        case ROOK11:
        case ROOK22:
        case ROOK21:
            return "rook";
            break;
        default:
            return "";
            break;
    }
}

void updateLog(int usr, int x, int y) {
    if(logIdx>=19) {
        int idx = 0;
        for (int i = 0; i < logIdx; i++, idx++) {
            for (int j = 0; j < 4; j++) {
                logInfo[i][j]=logInfo[i+1][j];
            }
            printfColorAt("Player %d moves to row %d, column %d", logInfo[i][0]==1 ? BLUE:RED,BLACK,700,20*(2+idx),logInfo[i][0],logInfo[i][2],logInfo[i][1]);
            if(logInfo[i][3]!=0) {
                idx++;
                printfColorAt("Player %d captures %s",logInfo[i][0]==1 ? BLUE:RED,BLACK,700,20*(2+idx),logInfo[i][0],pieceString(logInfo[i][3]));
            }
        }
        logIdx = idx;        
    }

    printfColorAt("Player %d moves to row %d, column %d", usr==1 ? BLUE:RED,BLACK,700,20*(2+logIdx),usr,y+1,x+1);
    logInfo[logCount][0] = usr;
    logInfo[logCount][1] = x+1;
    logInfo[logCount][2] = y+1;

    if(get_piece(usr_pos[X], usr_pos[Y]) != NO_PIECE) {
        logInfo[logCount][3] = get_piece(usr_pos[X], usr_pos[Y]);
        printfColorAt("Player %d captures %s",logInfo[logCount][0]==1 ? BLUE:RED,BLACK,700,20*(3+logIdx),logInfo[logCount][0],pieceString(logInfo[logCount][3]));
        logIdx++;
    }

    logCount++;
    logIdx++;
    printfColorAt("LOG IDX: %d",BLACK,GREEN,700,430,logIdx);
}

void table(){
    printfColorAt("To return to terminal press q",YELLOW,BLACK,700,info[1]-200);
    printfColorAt("To rotate board press r",YELLOW,BLACK,700,info[1]-150);
    printfColorAt("To make enroque press e",YELLOW,BLACK,700,info[1]-150);
    printfColorAt("Pieces of player 1 left :",YELLOW,BLACK,700,info[1]-100);
    printfColorAt("Pieces of player 2 left :",YELLOW,BLACK,700,info[1]-50);
    printfColorAt("Time :",YELLOW,BLACK,700,info[1],time.tick/18);
    tableData();
}

//Data de cuantas piezas siguen en juego y cuanto tiempo paso
void tableData(){
    printfColorAt("%d",YELLOW,BLACK,950,info[1]-100,set1.left);
    printfColorAt("%d",YELLOW,BLACK,950,info[1]-50,set2.left);
    printfColorAt("%d",YELLOW,BLACK,750,info[1],time.tick/18);
}