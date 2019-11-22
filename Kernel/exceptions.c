#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x20




static void zero_division();


void exceptionDispatcher(int exception, void * firstParam) {

	
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO");
				
				break;
			}
			case INVALID_OPCODE_EXCEPTION_ID:
			{
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION");
			}
		}
}





