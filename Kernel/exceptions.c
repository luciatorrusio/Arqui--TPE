#include <Curses.h>
#include <stdint.h>
#include <String.h>
#include <stdbool.h>
#include <Debugger.h>
#include <KernelHelper.h>

#define ZERO_EXCEPTION_ID 0
#define CUSTOM_EXCEPTION 0x20




static void zero_division();


static bool isShown = false;

void exceptionDispatcher(int exception, void * firstParam) {

	if(!isShown){
	
		switch(exception){
			case ZERO_EXCEPTION_ID:
			{
				PrintExceptionDetails("DIVISION BY ZERO");
				
				break;
			}
			case CUSTOM_EXCEPTION:
			{
				break;
			}
			default:{
				PrintExceptionDetails("UNKNOWN EXCEPTION");
			}
		}
		isShown = false;
			((EntryPoint)sampleCodeModuleAddress)();

	}
	

	

}





