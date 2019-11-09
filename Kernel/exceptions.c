#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <deviceInfo.h>

#define ZERO_EXCEPTION_ID 0
#define CUSTOM_EXCEPTION 1




static void zero_division();


static bool isShown = false;

void exceptionDispatcher(int exception, void * firstParam) {

	if(!isShown){

	switch(exception){
		case ZERO_EXCEPTION_ID:
		{
			PrintExceptionDetails("DIVISION BY ZERO")
			break;
		}
		case CUSTOM_EXCEPTION:
		{
			PrintExceptionDetails(firstParam);
			break;
		}
	}

	isShown = true;

}

static void zero_division() {

	PrintExceptionDetails("ZERO");
}



void PrintExceptionDetails(char * name){

	char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};
	Registers reg = getRegisters();

	clearConsole();
	
	//setColor(Red,Black);
	println("EXCEPTION: ");
	println(name);
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