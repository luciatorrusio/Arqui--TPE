#include "include/ConsoleDriver.h"
#include <VideoDriver.h>
#include <String.h>
#include <Debugger.h>

/***************************************************************/
/*                         CONSTANTES                          */
/***************************************************************/
#define MAX_ROWS 80
#define MAX_COLS 500

/***************************************************************/
/*                          VARIABLES                          */
/***************************************************************/

static int charHeight;
static int charWidth;
static int screenHeight;
static int screenWidth;

static int realRows;
static int realCols;

static char Buffer[MAX_ROWS][MAX_COLS];

static int topBufferIndex = 1;
static int endBufferIndex = 1;

static int fontColor = 0xFFFFFF;
static int backgroundColor = 0x0;

/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

int analizeNewString(char * string);

void __nextColumn();


/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_){
    charHeight = charHeight_;
    charWidth = charWidth_;
    screenHeight = screenHeight_;
    screenWidth = screenWidth_;

    realCols = screenWidth / charWidth;
    realRows = screenHeight / charHeight;
}



void printLine(char * string){

    printLineColor(string,fontColor,backgroundColor);
}

void printLineColor(char * string, int fontColor, int backgroundColor){
// Cargo en memoria al string nuevo, ya separado en los arreglos que se van a imprimir.
// Por la diferencia entre bottom y top puedo sacar cuantas lineas voy a tener que escribir
    int lenght = strlen(Buffer[topBufferIndex]);
    int bottomBufferIndex = topBufferIndex;

    for(int i = 0 ; string[i]!= 0 ;i++){        
        if(lenght >= realCols-1){
            Buffer[topBufferIndex][realCols-1] = 0;
            __nextColumn();
            lenght = 0;
        }
        if(string[i] == '\n'){
            Buffer[topBufferIndex][lenght] = 0;
            __nextColumn();
            lenght = 0;

        }else{
            Buffer[topBufferIndex][lenght++] = string[i];  
        }

    }
    Buffer[topBufferIndex][lenght++] = 0;
    

    int tempIndex = endBufferIndex;

    int printindex =1+ (endBufferIndex < topBufferIndex)?topBufferIndex -endBufferIndex :(realRows-endBufferIndex)+topBufferIndex  ;
    
    while (tempIndex != (topBufferIndex+1)% realRows)
    {
        for(int t = 0 ; t < realCols ;t++)
            drawChar(t * charWidth,screenHeight -(printindex+1) * charHeight,Buffer[tempIndex][t],fontColor,backgroundColor);
        for (int j = 0; Buffer[tempIndex][j] != 0; j++)
        {
            drawChar(  j * charWidth,screenHeight -(printindex+1) * charHeight,Buffer[tempIndex][j],fontColor,backgroundColor);
        }  
        printindex--;
        tempIndex = (tempIndex+1) % realRows;
    }

}

void printChar(char ch){

    int lenght = strlen(Buffer[topBufferIndex]);

    if(lenght >= realCols-1){
        Buffer[topBufferIndex][realCols-1] = 0;
        __nextColumn();
        lenght = 0;
    }
    if( ch == '\n'){
        Buffer[topBufferIndex][lenght] = 0;
        __nextColumn();
        lenght = 0;

    }else{
        Buffer[topBufferIndex][lenght++] = ch;  
    }


    Buffer[topBufferIndex][lenght] = 0;


    int tempIndex = endBufferIndex;

    int printindex =1+ (endBufferIndex < topBufferIndex)?topBufferIndex -endBufferIndex :(realRows-endBufferIndex)+topBufferIndex  ;

    while (tempIndex != (topBufferIndex+1)% realRows)
    {
        for(int t = 0 ; t < realCols ;t++)
            drawChar(t * charWidth,screenHeight -(printindex+1) * charHeight,Buffer[tempIndex][t],fontColor,backgroundColor);
        for (int j = 0; Buffer[tempIndex][j] != 0; j++)
        {
            drawChar(  j * charWidth,screenHeight -(printindex+1) * charHeight,Buffer[tempIndex][j],fontColor,backgroundColor);
        }  
        printindex--;
        tempIndex = (tempIndex+1) % realRows;
    }
}

void clearConsole(){
 
     for(int i = 0 ; i < realRows ; i++){
        for(int j = 0 ; j < realCols ; j++){
            Buffer[i][j] = 0;
            drawChar(charWidth * j, charHeight * i,' ',fontColor,backgroundColor);
        }
    }

    endBufferIndex = 1;
    topBufferIndex = 1;
    
}



/***************************************************************/
/*                    Funciones Privadas                       */
/***************************************************************/

int analizeNewString(char * string){

    int repetitions = countRepetitionsOf(string,'\n');

    if (string[strlen(string)] == '\n')
        repetitions--;

    return repetitions;
}

void __nextColumn(){

    topBufferIndex = (topBufferIndex+1) % realRows;

    if((topBufferIndex+1) % realRows == endBufferIndex){

        for(int i = 0 ; i < realCols ; i++)
            Buffer[endBufferIndex][i] = 0;
        endBufferIndex = (endBufferIndex+1) % realRows;
    }
}