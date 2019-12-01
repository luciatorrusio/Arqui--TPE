#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 0x06




void exceptionDispatcher(int exception, uint64_t * stackPointer) {
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO",stackPointer,*(stackPointer+15));
				// Esta instruccion solo salta cuando se usan las instrucciones DIV y IDIV, 
				// y funciona con ambas insutrcciones.
				//*(stackPointer+15)  = *(stackPointer + 10);
				break;
			}
			case INVALID_OPCODE_EXCEPTION_ID:
			{
				PrintExceptionDetails("Invalid OPCODE",stackPointer,*(stackPointer+15));
				// Hay varias formas de que se salte esta excepcion. De esta forma salta si se usa a la 
				// instruccion UD2
				//*(stackPointer+15) = 0x400000;
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION",stackPointer,*(stackPointer+15));
			}

		}	
		// uint64_t * sp = * (stackPointer + 10);

		/*
			Yo que 	que al entrar en una funcion pusheo el RBP y copio el valor del RSP al EBP. Entoces
			el RBP tiene el puntero al stack que me interesa.
		*/
*(stackPointer+15) = 0x400000;
		// *(stackPointer+15)  = *(sp - 1);
		// *(stackPointer + 18) = sp;
		// *(stackPointer + 10) = *(sp);
	
}





