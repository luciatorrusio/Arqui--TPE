#include "../include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>
#include <deviceInfo.h>
#include <Time.h>
#include <ReadDispatcher.h>
#include <Debugger.h>
#include <SpeakerDriver.h>
#include <font.h>
#include <VideoDriver.h>
#include <ConsoleDriver.h>



#define FD_STDOUT 				(0x01)
#define FD_STDERR 				(0x02)
#define FD_STDIN 				(0x03)
#define FD_SPEAKER 				(0x04)
#define FD_SQUARES 				(0x05)
#define FD_MEMORY 				(0x06)
#define FD_REGISTERS			(0x07)
#define FD_DEVICE_INFO 			(0x08)
#define FD_TIMER				(0x09)
#define FD_TIME					(0x0A)
#define FD_STDOUT_COLOR			(0x0B)

#define DELETE_CURRENT_CHAR 1
#define DELETE_ALL_DISPLAY 3



void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchDelete(void * fd);
void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);


static void int_20();
// static void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam);
// static void int_83(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam,void * fifthParam);


static void int_21();
void int_82(int timeID, int * value);


static void int_81(int id, void * firstParam,void * secondParam,void * thirdParam);

void irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam,void * fourthParam,void * fifthParam) {


	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
		case 0x80:
			// int_80(firstParam,secondParam,thirdParam,fourthParam);
			dispatchRead(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
		case 0x81:

			dispatchWrite(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			//int_81(firstParam,secondParam,thirdParam,fourthParam);
		break;
		case 0x82:
			dispatchDelete(firstParam);
			//int_82(firstParam,secondParam);
			break;
		case 0x83:
			// int_83(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
	
	}
}

void int_20() {
	timer_handler();
}

void int_21(){

	 readKey();
	
}





void dispatchRead(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){

	switch(fd){
		case FD_STDOUT: { break;}
		case FD_STDERR: { break;}
		case FD_STDIN: { 

			char * buffer = (char *) firstParam;
            int bufferSize = secondParam;
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
		case FD_SPEAKER: { break;}
		case FD_SQUARES: { break;}
		case FD_MEMORY: { 
			
			// printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.",fd,firstParam,secondParam,thirdParam,fourthParam);
			uint64_t position = firstParam;
			char * buff = secondParam;
			int size = thirdParam;

			readMem(position,buff,size);


			break;
		}
		case FD_REGISTERS: { 
			getRegisters(firstParam,secondParam,thirdParam);
			break;
		}
		case FD_DEVICE_INFO: { 
			getDeviceInfo(firstParam);
			break;
		}
		case FD_TIMER: { 

			uint64_t * ticks = firstParam;
            *ticks = ticks_elapsed();	
			break;
		}
		case FD_TIME: { 
			 printf("FD: %d. PAR1 %d. PAR2 %d. PAR3 %d. PAR4 %d.\n",fd,firstParam,secondParam,thirdParam,fourthParam);
			int * value = secondParam;
			*value = handleTimeRequest(firstParam);

			printf("VALUE: %d\n",*value);
			break;
			}
		case FD_STDOUT_COLOR: { break;}
	}
}


void int_81(int id, void * firstParam,void * secondParam,void * thirdParam){
	//printf("En Kernel.ID que mande: %d\n",id);

	switch (id)
	{
		case 0x01: // READMEM
		{
			// uint64_t position = firstParam;
			// char * buff = secondParam;
			// unsigned size = thirdParam;

			// readMem(position,buff,size);

			break;
		}
		case 0x02: // GETREGISTERS
		{
			// getRegisters(firstParam,secondParam,thirdParam);
			return;
			break;
		}
		case 0x03:{
			// getBpp(firstParam);
			return;
			break;
		}
		case 0x04:{
			// setSize(firstParam);
			return;
			break;
		}
		case 0x05:{
			// unsigned int * aux=firstParam;
			// *aux=CHAR_HEIGHT;
			return;
			break;
		}
		case 0x06:{
			// unsigned int * aux=firstParam;
			// *aux=CHAR_WIDTH;
			return;
			break;
		}
		default:{
			printf("ID que mande: %d",id);
		}
	}
}

void int_82(int timeID, int * value){
	*value = handleTimeRequest(timeID);
}



void dispatchDelete(void * fd){
	switch ((int)fd)
	{
		case DELETE_CURRENT_CHAR:{
			removeLastChar();
			break;
		}
		case DELETE_ALL_DISPLAY:{
			clearConsole();
			break;
		}
	}
}



void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam){
	char * buffer = firstParam;

	switch(fd){
		case FD_STDOUT:{

            if(buffer[1] == 0)
                putChar(*buffer);
			else
                printf(buffer);
	
			break;

			return;
		}
		case FD_STDERR:{
                
			if(buffer[1] == 0)
			   putCharColor(*buffer,0xFF0000,0x0000);
			else
				printfColor(buffer,0xFF0000,0x0000);
            break;
        }
		case FD_STDIN: break;
        case FD_SPEAKER:{
            beep();
            break;
        }
		case FD_SQUARES:{ 
			int * pos = firstParam;
			int length = secondParam;
			int height=thirdParam;
			int fontColor=fourthParam;
			
			print(pos,length,height,fontColor);
			break;
			}
		case FD_MEMORY: break;
		case FD_REGISTERS: break;
		case FD_DEVICE_INFO: {
			setSize(firstParam);
			break;
		}
		case FD_TIMER: break;
		case FD_TIME: break;
		case FD_STDOUT_COLOR:{
			 printLineColorAt(firstParam);

			break;
		}
	}
	
}



