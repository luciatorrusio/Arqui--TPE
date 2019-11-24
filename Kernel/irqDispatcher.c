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

#define FD_STDOUT 				(0x01)
#define FD_STDERR 				(0x02)
#define FD_STDIN 				(0x03)
#define FD_SPEAKER 				(0x04)
#define FD_SQUARES 				(0x05)
#define FD_MEMORY 				(0x06)
#define FD_REGISTERS			(0x07)
#define FD_SCREENCONFIG 		(0x08)
#define FD_TIMER				(0x09)
#define FD_TIME					(0x0A)

#define ID_WRITE				(0x01)
#define ID_DELETE				(0x02)
#define ID_READ					(0x03)


void dispatchWrite(int fd,void * firstParam, void * secondParam,void * thirdParam,void * fourthParam);
void dispatchDelete(void * fd);



static void int_20();
static void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam);
static void int_83(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam,void * fifthParam);


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
			int_80(firstParam,secondParam,thirdParam,fourthParam);
			break;
		case 0x81:

			dispatchWrite(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			int_81(firstParam,secondParam,thirdParam,fourthParam);
		break;
		case 0x82:
			int_82(firstParam,secondParam);
			break;
		case 0x83:
			int_83(firstParam,secondParam,thirdParam,fourthParam,fifthParam);
			break;
	
	}
}

void int_20() {
	timer_handler();
}

void int_21(){

	 readKey();
	
}

void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam){
	int id = firstParam;
	int fileDescriptor = secondParam;
	char * buffer = (char *) thirdParam;

	
	switch (id)
	{
		case ID_WRITE:{ 

			//dispatchWrite(fileDescriptor,secondParam,thirdParam,fourthParam);


			
			break;
		}
		case 2:{ // Delete
			dispatchDelete(secondParam);
            break;
		}
		case 3: // read
		{
			dispatchRead(secondParam,thirdParam,fourthParam);
			break;
		}
		case 4:
		{
			printLineColorAt(secondParam);
				break;
		}
	}
}


void int_81(int id, void * firstParam,void * secondParam,void * thirdParam){
	//printf("En Kernel.ID que mande: %d\n",id);

	switch (id)
	{
		case 0x01: // READMEM
		{
			uint64_t position = firstParam;
			char * buff = secondParam;
			unsigned size = thirdParam;

			readMem(position,buff,size);

			break;
		}
		case 0x02: // GETREGISTERS
		{
			getRegisters(firstParam,secondParam,thirdParam);
			return;
			break;
		}
		case 0x03:{
			getBpp(firstParam);
			return;
			break;
		}
		case 0x04:{
			setSize(firstParam);
			return;
			break;
		}
		case 0x05:{
			unsigned int * aux=firstParam;
			*aux=CHAR_HEIGHT;
			return;
			break;
		}
		case 0x06:{
			unsigned int * aux=firstParam;
			*aux=CHAR_WIDTH;
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

#define CURRENT_CHAR 1
#define ALL_DISPLAY 2
#include <ConsoleDriver.h>

void dispatchDelete(void * fd){
	switch ((int)fd)
	{
		case CURRENT_CHAR:{
			removeLastChar();
			break;
		}
		case ALL_DISPLAY:{
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
		case FD_SCREENCONFIG: break;
		case FD_TIMER: break;
		case FD_TIME: break;
	}
}


void int_83(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam,void * fifthParam){
	int id = firstParam;
	// int * pos = secondParam;
	// int length = thirdParam;
	// int height=fourthParam;
	// int fontColor=fifthParam;
	

	// print(pos,length,height,fontColor);
}


