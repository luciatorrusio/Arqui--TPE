#include "../Include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>

static void int_20();
static void int_80(void * firstParam,void * secondParam);
static void int_81(void * firstParam, void * secondParam, void * thirdParam);
static void int_21();

void irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam ) {

	switch (irq) {
		case 0:
			int_20();
			break;
		case 0x21:
		case 1:
			int_21();
			break;
		case 0x80:
			int_80(firstParam,secondParam);
			break;
		case 0x81:
			
			int_81(firstParam,secondParam,thirdParam);
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

void int_80(void * firstParam,void * secondParam){
	int fileDescriptor = firstParam;
	char * buffer = secondParam;


	Color currentTextColor;
	Color currentBackgroundColor;

	if(fileDescriptor == 2){
		getColor(&currentTextColor,&currentBackgroundColor);
		setColor(White,Red);
	}

	println(buffer);
	
	if(fileDescriptor == 2)
		setColor(currentTextColor,currentBackgroundColor);
	
}

static void int_81(void * firstParam, void * secondParam, void * thirdParam){
	int fileDescriptor = firstParam;
	char * buffer = secondParam;
	unsigned int position = thirdParam;

	Color currentTextColor;
	Color currentBackgroundColor;
	
	if(fileDescriptor == 2){
		getColor(&currentTextColor,&currentBackgroundColor);
		setColor(White,Red);
	}

	printlnAt(buffer,position);

	if(fileDescriptor == 2)
		setColor(currentTextColor,currentBackgroundColor);
}

void int_21(){

	 readKey();

	int temp = returnKey();
	if( temp != -1)
	 	printChar(temp);
	
}


	
