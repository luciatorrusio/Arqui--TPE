#include "../Include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>
#include <deviceInfo.h>

static void int_20();
static void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam);
static void int_21();

static void int_81(int id, void * firstParam,void * secondParam,void * thirdParam);

void irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam,void * fourthParam ) {

	switch (irq) {
		case 0:
			int_20();
			break;
		case 0x21:
		case 1:
			int_21();
			break;
		case 0x80:
			int_80(firstParam,secondParam,thirdParam,fourthParam);
			break;
		case 0x81:
			int_81(firstParam,secondParam,thirdParam,fourthParam);
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

	Color currentTextColor,currentBackgroundColor;
	
	switch (id)
	{
		case 1:{

			if(fileDescriptor == 2){
				getColor(&currentTextColor,&currentBackgroundColor);
				setColor(White,Red);
			}

			println(buffer);
			
			if(fileDescriptor == 2)
				setColor(currentTextColor,currentBackgroundColor);

			break;
		}
		case 2:{

			uint64_t position = fourthParam;

			if(fileDescriptor == 2){
				getColor(&currentTextColor,&currentBackgroundColor);
				setColor(White,Red);
			}

			printlnAt(buffer,position);

			if(fileDescriptor == 2)
				setColor(currentTextColor,currentBackgroundColor);

			break;
		}
		case 3: 
		{
			int bufferSize = fourthParam;
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
	}
}





void int_81(int id, void * firstParam,void * secondParam,void * thirdParam){

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
			Registers reg = getRegisters();
			Registers * returnAdress = firstParam;
		
			*returnAdress = reg;

			break;
		}
	}
}


	
