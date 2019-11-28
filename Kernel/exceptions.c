#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x06




void exceptionDispatcher(int exception, uint64_t * stackPointer,void * secondParam) {
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO",stackPointer,*(stackPointer+17));
				
				break;
			}
			case INVALID_OPCODE_EXCEPTION_ID:
			{
				PrintExceptionDetails("Invalid OPCODE",stackPointer,*(stackPointer+17));
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION",stackPointer,*(stackPointer+17));
			}

		}
//		*(stackPointer+17)=*(stackPointer+9);
		
}





