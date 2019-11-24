#include "../include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>
#include <deviceInfo.h>
#include <Time.h>
#include <ReadDispatcher.h>
#include <Debugger.h>
#include <VideoDriver.h>
#include <font.h>

static void int_20();
static void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam);
static void int_21();
void int_82(int timeID, int * value);

void dispatchDelete(void * fd);

static void int_81(int id, void * firstParam,void * secondParam,void * thirdParam);

void irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam,void * fourthParam ) {


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
			int_81(firstParam,secondParam,thirdParam,fourthParam);
		break;
		case 0x82:
			int_82(firstParam,secondParam);
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
		case 1:{ // write
			if(fileDescriptor == 2){
				if(buffer[1] == 0)
					putCharColor(*buffer,0xFF0000,0x0000);
				else
					printfColor(buffer,0xFF0000,0x0000);
			}
			else{
				if(buffer[1] == 0)
					putChar(*buffer);
				else
					printf(buffer);
			}

				
			break;
		}
		case 2:{ // Delete
			dispatchDelete(secondParam);
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

