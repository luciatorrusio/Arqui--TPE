#include "../include/timer.h"
#include <stdint.h>
#include <Curses.h>
#include <String.h>
#include <keyboard.h>
#include <deviceInfo.h>
#include <Time.h>
#include <ReadDispatcher.h>

static void int_20();
static void int_80(void * firstParam,void * secondParam,void * thirdParam,void * fourthParam);
static void int_21();
void int_82(int timeID, int * value);

static void int_81(int id, void * firstParam,void * secondParam,void * thirdParam);
static void int_85(char * firstParam);

static int _85Control = 0;

void irqDispatcher(uint64_t irq, void * firstParam,void * secondParam, void * thirdParam,void * fourthParam ) {

	switch (irq) {
		case 0:
			int_20();
			break;
		case 0x21:
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
		case 0x85:{		
			
			int_85(firstParam);

			break;
		}
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
		case 1:{ // write

			if(fileDescriptor == 2){
				getColor(&currentTextColor,&currentBackgroundColor);
				setColor(White,Red);
			}

			println(buffer);
			
			if(fileDescriptor == 2)
				setColor(currentTextColor,currentBackgroundColor);

			break;
		}
		case 2:{ // write at

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
		case 3: // read
		{
			dispatchRead(secondParam,thirdParam,fourthParam);
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

void int_82(int timeID, int * value){
	*value = handleTimeRequest(timeID);
}

void int_85(char * firstParam){



	char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};
	Registers reg = getRegisters();

	clearConsole();
	
	//setColor(Red,Black);
	println("EXCEPTION: ");
	println(firstParam);
	println("  @ IP: 0X");

	HexToString(temp,17,reg.rip);
	println(temp);

	println("\nRAX: 0X");
	HexToString(temp,17,reg.rax);
	println(temp);
	
	println("\nRBX: 0X");
	HexToString(temp,17,reg.rbx);
	println(temp);

	
	println("\nRCX: 0X");
	HexToString(temp,17,reg.rcx);
	println(temp);

	
	println("\nRDX: 0X");
	HexToString(temp,17,reg.rdx);
	println(temp);
	
	println("\nRSI: 0X");
	HexToString(temp,17,reg.rsi);
	println(temp);
	
	println("\nRDI: 0X");
	HexToString(temp,17,reg.rdi);
	println(temp);
	
	println("\nR8:  0X");
	HexToString(temp,17,reg.r8);
	println(temp);

	println("\nR9:  0X");
	HexToString(temp,17,reg.r9);
	println(temp);

	println("\nR10: 0X");
	HexToString(temp,17,reg.r10);
	println(temp);

	println("\nR11: 0X");
	HexToString(temp,17,reg.r11);
	println(temp);

	println("\nR12: 0X");
	HexToString(temp,17,reg.r12);
	println(temp);

	println("\nR13: 0X");
	HexToString(temp,17,reg.r13);
	println(temp);

	println("\nR14: 0X");
	HexToString(temp,17,reg.r14);
	println(temp);

	println("\nR15: 0X");
	HexToString(temp,17,reg.r15);
	println(temp);

}
