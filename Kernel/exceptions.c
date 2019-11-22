#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x06




static void zero_division();


void exceptionDispatcher(int exception, void * firstParam,void * secondParam) {

	
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO",firstParam,secondParam);
				
				break;
			}
			case INVALID_OPCODE_EXCEPTION_ID:
			{
				PrintExceptionDetails("Invalid OPCODE",firstParam,secondParam);
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION",firstParam,secondParam);
			}
		}

		
}





