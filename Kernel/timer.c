#include "../include/timer.h"
#include <naiveConsole.h>
#include <stdlib.h>

static unsigned long ticks = 0;

static char * str = NULL;
static int interval = 0;
void printString();

void timer_handler() {
		ticks++;	
		printString();
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void setString(char * str2, int interval2){
	//ncClear();
	str = str2;
	interval = interval2;

	//ncPrintDec(interval2);

}

void printString(){
	if(str != NULL && interval != 0){
		if(ticks_elapsed() % (18 *interval) == 0){
			//ncPrint((char*)str);
			//ncNewline();
		}
	}
}

