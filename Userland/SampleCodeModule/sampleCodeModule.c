/* sampleCodeModule.c */
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/String.h"
#include "../Include/Syscalls.h"

#include "include/Terminal.h"

#include <stdlib.h>

void printCurrentTime();


int main() {

	runTerminal();

	return 0xDEA;
}


void printCurrentTime(){
	char * HoraText = "La hora actual es:   ";
	char * separador = " : ";
	char * FechaSemanaText = "El dia actual en la semana es:  ";
	char * FechaMesText = "El dia actial del mes es:  ";
	char * MesText = "Es el mes numero:  ";
	char * AnoText = "Es el ano:  ";


		moveCursor(1,3);

		char seconds[3] = {'0','0',0};
		char minutes[3] = {'0','0',0};
		char hours[3] = {'0','0',0};
		char year[5] = {'0','0','0','0',0};
		char month[3]= {'0','0',0};
		char dayInMonth[3] = {'0','0',0};
		char dayInWeek[2] = {'0',0};

		IntToString(seconds,3,GetSeconds());
		IntToString(minutes,3,GetMinutes());
		IntToString(hours,3,GetHours());

		IntToString(year,5,GetYear());
		IntToString(month,3,GetMonth());

		IntToString(dayInMonth,3,GetDayOfMonth());
		IntToString(dayInWeek,2,GetDayOfWeek());

		// println(NULL,HoraText);
		// println(NULL,hours);
		// println(NULL,separador);
		// println(NULL,minutes);
		// println(NULL,separador);
		// println(NULL,seconds);

		moveCursor(3,3);
		// println(NULL,FechaSemanaText);
		// println(NULL,dayInWeek);

		moveCursor(4,3);
		// println(NULL,FechaMesText);
		// println(NULL,dayInMonth);

		moveCursor(5,3);
		// println(NULL,MesText);
		// println(NULL,month);

		moveCursor(6,3);
		// println(NULL,AnoText);
		// println(NULL,year);

	
}