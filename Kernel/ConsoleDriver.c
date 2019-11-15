#include "include/ConsoleDriver.h"
#include <VideoDriver.h>
#include <String.h>
#include <Debugger.h>

/***************************************************************/
/*                         CONSTANTES                          */
/***************************************************************/
#define MAX_ROWS 80  // old
#define MAX_COLS 500 //old

#define MAX_BUFFER_SIZE (10000)

#define DEFAULT_FONT_COLOR (0xFFFFFF)
#define DEFAULT_BACKGROUND_COLOR (0x000000)

/***************************************************************/
/*                          VARIABLES                          */
/***************************************************************/

static int charHeight;
static int charWidth;
static int screenHeight;
static int screenWidth;

static int realRows;    //OLD
static int realCols;    //OLD

static ColorChar MatrixBuffer[MAX_ROWS][MAX_COLS];//OLD
static int topBufferIndex = 1;//OLD
static int endBufferIndex = 1;//OLD

static ColorChar Buffer[MAX_BUFFER_SIZE];
static int currPosition = 0;
static int previusCurrPosition = 0;


/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void __nextColumn();
void reflectBufferChangesToDisplay();

int countRepetitionsOfColorString(ColorChar * str, char ch);
int strlenColorString(ColorChar* str);
void appendColorString(ColorChar * src, ColorChar * dest, int bufferSize);
void removeColorString(ColorChar * str, int pos);
int findLastReferenceOfColorString(ColorChar * buffer, int initialPosition, char element);


/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_){
    charHeight = charHeight_;
    charWidth = charWidth_;
    screenHeight = screenHeight_;
    screenWidth = screenWidth_;

    realCols = screenWidth / charWidth;
    realRows =  screenHeight / charHeight;
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

static int currentRows = 0;

void printLineColor(ColorChar * string){

    currPosition = strlenColorString(Buffer);

    for( previusCurrPosition = currPosition ; 
            currPosition < MAX_BUFFER_SIZE && string[currPosition - previusCurrPosition].ch != 0;
            currPosition++){
        if(string[currPosition-previusCurrPosition].ch == '\n')
            currentRows++;
        Buffer[currPosition] = string[currPosition-previusCurrPosition];
    }

    Buffer[currPosition].ch = 0;

    reflectBufferChangesToDisplay();
}

void printChar(char ch){

    ColorChar temp;
    temp.ch = ch;
    temp.backgroundColor = DEFAULT_BACKGROUND_COLOR;
    temp.fontColor = DEFAULT_FONT_COLOR;

    printCharColor(temp);    
}

void printCharColor(ColorChar ch){

    previusCurrPosition = currPosition++;

    Buffer[previusCurrPosition] = ch;
    Buffer[currPosition].ch = 0;
    

    reflectBufferChangesToDisplay();

   
}

void clearConsole(){
 
     for(int i = 0 ; i < realRows ; i++){
        for(int j = 0 ; j < realCols ; j++){
            MatrixBuffer[i][j].ch = 0;
            drawChar(charWidth * j, charHeight * i,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);
        }
    }

    endBufferIndex = 1;
    topBufferIndex = 1;
    
}



/***************************************************************/
/*                    Funciones Privadas                       */
/***************************************************************/

void reflectBufferChangesToDisplay(){

    if(Buffer[currPosition-1].ch == '\n'){
        int rows = 1+ currentRows;

        int x = 0, y = screenHeight - rows * charHeight;

        for(int i = 0 ; Buffer[i].ch != 0 ; i++){
            if(Buffer[i].ch == '\n' || x >= screenWidth){
                if (y >= 0 ){
                    for(int tempx = x; tempx < screenWidth ; tempx += charWidth)
                        drawChar(tempx,y,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);
                }
                if(Buffer[i].ch == '\n'){

                    int spacesToDelete = findLastReferenceOfColorString(Buffer,currPosition-2,'\n');
                    for(int xtemp = 0 ; xtemp < spacesToDelete ; xtemp++)
                        drawChar(xtemp * charWidth,screenHeight - charHeight,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);                    
                }
                y += charHeight;
                x = 0;
            }else if (y >= 0 ){
                drawChar(x,y,Buffer[i].ch,Buffer[i].fontColor,Buffer[i].backgroundColor);
                x+= charWidth;
            }
        }
    }else{
        int x = -1;
        for(int i = currPosition-1; i >= 0 && Buffer[i].ch != '\n'; i--)
            x++;
        drawChar(x * charWidth,screenHeight - charHeight,Buffer[currPosition-1].ch,Buffer[currPosition-1].fontColor,Buffer[currPosition-1].backgroundColor);


    }

}

int strlenColorString(ColorChar* str){
    int i = 0;
    while(str[i].ch!=0){
        i++;
    }
    return i;
}

int findLastReferenceOfColorString(ColorChar * buffer, int initialPosition, char element){
    int counter = 0;
    for(int i = initialPosition ; i >= 0 && buffer[i].ch != element;i--){
        counter++;
    }
    return counter;
}

void removeColorString(ColorChar * str, int pos){
    for(int i = pos; str[i].ch != 0 ; i++ ){

        str[i] = str[i+1];

    }
}




void appendColorString(ColorChar * src, ColorChar * dest, int bufferSize){
    int base = strlenColorString(dest);
    int i;
	for( i = 0 ; base + i-1 < bufferSize && src[i].ch != 0 ; i++){
		dest[base + i] = src[i];
        dest[base + i+1].ch = 0;

	}
}

int countRepetitionsOfColorString(ColorChar * str, char ch){
    int count = 0;
	for( int i = 0 ; str[i].ch != 0; i++)
		if(str[i].ch == ch)
			count++;

	return count;
}

void __nextColumn(){

    topBufferIndex = (topBufferIndex+1) % MAX_ROWS;

    int distance = (topBufferIndex >= endBufferIndex)? 
                    topBufferIndex - endBufferIndex:
                    topBufferIndex + (MAX_ROWS -endBufferIndex);

    while(distance > realRows){

        for(int i = 0 ; i < realCols ; i++)
            MatrixBuffer[endBufferIndex][i].ch = 0;
        endBufferIndex = (endBufferIndex+1) % MAX_ROWS;
        distance--;

    }
}