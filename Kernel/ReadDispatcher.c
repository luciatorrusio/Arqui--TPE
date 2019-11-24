#include <ReadDispatcher.h>
#include <Curses.h>
#include <timer.h>
#include <stdint.h>



void dispatchReadd(void * firstParam,void * secondParam,void * thirdParam){
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

            break;
        }
        case 4: // Timer
        {
            uint64_t * ticks = secondParam;

            *ticks = ticks_elapsed();
            break;
        }
    }



}