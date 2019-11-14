#include "include/ConsoleDriver.h"
#include <VideoDriver.h>
#include <String.h>
#include <Debugger.h>

/***************************************************************/
/*                         CONSTANTES                          */
/***************************************************************/
#define MAX_ROWS 80
#define MAX_COLS 500

#define DEFAULT_FONT_COLOR (0xFFFFFF)
#define DEFAULT_BACKGROUND_COLOR (0x000000)

/***************************************************************/
/*                          VARIABLES                          */
/***************************************************************/

static int charHeight;
static int charWidth;
static int screenHeight;
static int screenWidth;

static int realRows;
static int realCols;

static ColorChar Buffer[MAX_ROWS][MAX_COLS];

static int topBufferIndex = 1;
static int endBufferIndex = 1;


/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void __nextColumn();

int countRepetitionsOfColorString(ColorChar * str, char ch);
int strlenColorString(ColorChar* str);



/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_){
    charHeight = charHeight_;
    charWidth = charWidth_;
    screenHeight = screenHeight_;
    screenWidth = screenWidth_;

    realCols = screenWidth / charWidth;
    realRows = 10;// screenHeight / charHeight;
}



void printLine(char * string){
    int lenght = strlen(string);

    ColorChar temp[lenght];
    int i;

    for( i = 0 ; string[i]!=0 ; i++){
        temp[i].ch = string[i];
        temp[i].fontColor = DEFAULT_FONT_COLOR;
        temp[i].backgroundColor = DEFAULT_BACKGROUND_COLOR;
    }

    temp[i].ch = 0;
    temp[i].fontColor = DEFAULT_FONT_COLOR;
    temp[i].backgroundColor = DEFAULT_BACKGROUND_COLOR;

    printLineColor(temp);
}

void printLineColor(ColorChar * string){
// Cargo en memoria al string nuevo, ya separado en los arreglos que se van a imprimir.
// Por la diferencia entre bottom y top puedo sacar cuantas lineas voy a tener que escribir

    int lenght = strlenColorString(Buffer[topBufferIndex]);
    int bottomBufferIndex = topBufferIndex;


    for(int i = 0 ; string[i].ch!= 0 ;i++){        
        if(lenght >= realCols-1){
            Buffer[topBufferIndex][realCols-1].ch = 0;
            __nextColumn();
            lenght = 0;
        }
        if(string[i].ch == '\n'){
            Buffer[topBufferIndex][lenght].ch = 0;
            __nextColumn();
            lenght = 0;

        }else{
            Buffer[topBufferIndex][lenght++] = string[i];  
        }

    }
    Buffer[topBufferIndex][lenght++].ch = 0;
    

    int tempIndex = endBufferIndex;

    int printindex =1+ (endBufferIndex < topBufferIndex)?topBufferIndex -endBufferIndex :(realRows-endBufferIndex)+topBufferIndex  ;
    
    while (tempIndex != (topBufferIndex+1)% realRows)
    {
        for(int t = 0 ; t < realCols ;t++)
            drawChar(t * charWidth,screenHeight -(printindex+1) * charHeight,
                Buffer[tempIndex][t].ch,Buffer[tempIndex][t].fontColor,Buffer[tempIndex][t].backgroundColor);
        for (int j = 0; Buffer[tempIndex][j].ch != 0; j++)
        {
            drawChar( j * charWidth,screenHeight -(printindex+1) * charHeight,
                Buffer[tempIndex][j].ch,Buffer[tempIndex][j].fontColor,Buffer[tempIndex][j].backgroundColor);
        }  
        printindex--;
        tempIndex = (tempIndex+1) % realRows;
    }

}

void printChar(char ch){

    ColorChar temp;
    temp.ch = ch;
    temp.backgroundColor = DEFAULT_BACKGROUND_COLOR;
    temp.fontColor = DEFAULT_FONT_COLOR;

    printCharColor(temp);    
}

void printCharColor(ColorChar ch){
    int lenght = strlenColorString(Buffer[topBufferIndex]);

    if(lenght >= realCols-1){
        Buffer[topBufferIndex][realCols-1].ch = 0;
        __nextColumn();
        lenght = 0;
    }
    if(ch.ch == '\n'){
        Buffer[topBufferIndex][lenght].ch = 0;
        __nextColumn();
        lenght = 0;

    }else{
        Buffer[topBufferIndex][lenght++] = ch;  
    }


    Buffer[topBufferIndex][lenght].ch = 0;

    int tempIndex = endBufferIndex+1;

    int printindex =1+ (endBufferIndex < topBufferIndex)?topBufferIndex -endBufferIndex :(realRows-endBufferIndex)+topBufferIndex  ;

    while (tempIndex != (topBufferIndex+1)% realRows)
    {
        for(int t = 0 ; t < realCols ;t++)
            drawChar(t * charWidth,screenHeight -(printindex+1) * charHeight,
                Buffer[tempIndex][t].ch,Buffer[tempIndex][t].fontColor,Buffer[tempIndex][t].backgroundColor);
        for (int j = 0; Buffer[tempIndex][j].ch != 0; j++)
        {
            drawChar(  j * charWidth,screenHeight -(printindex+1) * charHeight,
                Buffer[tempIndex][j].ch,Buffer[tempIndex][j].fontColor,Buffer[tempIndex][j].backgroundColor);
        }  
        printindex--;
        tempIndex = (tempIndex+1) % realRows;
    }
}

void clearConsole(){
 
     for(int i = 0 ; i < realRows ; i++){
        for(int j = 0 ; j < realCols ; j++){
            Buffer[i][j].ch = 0;
            drawChar(charWidth * j, charHeight * i,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);
        }
    }

    endBufferIndex = 1;
    topBufferIndex = 1;
    
}



/***************************************************************/
/*                    Funciones Privadas                       */
/***************************************************************/


int strlenColorString(ColorChar* str){
    int i = 0;
    while(str[i].ch!=0){
        i++;
    }
    return i;
}

int countRepetitionsOfColorString(ColorChar * str, char ch){
    int count = 0;
	for( int i = 0 ; str[i].ch != 0; i++)
		if(str[i].ch == ch)
			count++;

	return count;
}

void __nextColumn(){

    topBufferIndex = (topBufferIndex+1) % realRows;

    if((topBufferIndex+1) % realRows == endBufferIndex){

        for(int i = 0 ; i < realCols ; i++)
            Buffer[endBufferIndex][i].ch = 0;
        endBufferIndex = (endBufferIndex+1) % realRows;
    }
}