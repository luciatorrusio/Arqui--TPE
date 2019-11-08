#include <ReadDispatcher.h>
#include <Curses.h>

typedef struct 
{
    int columns;
    int rows;

}VideoConfiguration;


void dispatchRead(void * firstParam,void * secondParam,void * thirdParam){
    int fd = firstParam;

    switch(fd){
        case 1: // STDIN
        {
            char * buffer = (char *) secondParam;
            int bufferSize = thirdParam;
			int i = 0;		
			int temp;
			do{
				temp = returnKey();
				
				if( temp != -1 ){
					buffer[i++]=temp;
				}

			}while( temp!= -1 && i <bufferSize-1 );


			buffer[i] = 0;

            break;
        }
        case 2: // TERMINAL CONFIGURATION
        {
            VideoConfiguration * config = secondParam;

            getScreenDimensions(&(config->columns), &(config->rows));
            break;
        }
    }



}