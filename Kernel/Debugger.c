#include "include/Debugger.h"
#include <deviceInfo.h>
#include <Curses.h>

void ThrowCustomException(char * str){
    PrintExceptionDetails(str);

    printfColor("\n\n\nPress any key to continue",0xFF0000,0xFFFFFF);

	do{
		readKey();
	}
	while (returnKey() == -1);

	clearConsole();
}

void PrintExceptionDetails(char * name){


	char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};
	Registers reg = getRegisters();

	//clearConsole();
	
	//setColor(Red,Black);
	printf("EXCEPTION: ");
	printf(name);
	printf("  @ IP: 0X");

	HexToString(temp,17,reg.rip);
	printf(temp);

	printf("\nRAX: 0X");
	HexToString(temp,17,reg.rax);
	printf(temp);
	
	printf("\nRBX: 0X");
	HexToString(temp,17,reg.rbx);
	printf(temp);

	
	printf("\nRCX: 0X");
	HexToString(temp,17,reg.rcx);
	printf(temp);

	
	printf("\nRDX: 0X");
	HexToString(temp,17,reg.rdx);
	printf(temp);
	
	printf("\nRSI: 0X");
	HexToString(temp,17,reg.rsi);
	printf(temp);
	
	printf("\nRDI: 0X");
	HexToString(temp,17,reg.rdi);
	printf(temp);
	
	printf("\nR8:  0X");
	HexToString(temp,17,reg.r8);
	printf(temp);

	printf("\nR9:  0X");
	HexToString(temp,17,reg.r9);
	printf(temp);

	printf("\nR10: 0X");
	HexToString(temp,17,reg.r10);
	printf(temp);

	printf("\nR11: 0X");
	HexToString(temp,17,reg.r11);
	printf(temp);

	printf("\nR12: 0X");
	HexToString(temp,17,reg.r12);
	printf(temp);

	printf("\nR13: 0X");
	HexToString(temp,17,reg.r13);
	printf(temp);

	printf("\nR14: 0X");
	HexToString(temp,17,reg.r14);
	printf(temp);

	printf("\nR15: 0X");
	HexToString(temp,17,reg.r15);
	printf(temp);
}

bool assertEqual(void * val1, void * val2){

    if(val1 == val2){
        char temp[100];
        char temp2 [20];

        append("Values EQUAL:  ",temp,100);
        IntToString(temp2,20,val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,val2);

        append(" == ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 == val2;
}

bool assertNotEqual(void * val1, void * val2){

        if(val1 != val2){
        char temp[100];
        char temp2 [20];

        append("Values NOT EQUAL:  ",temp,75);
        IntToString(temp2,20,val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,val2);

        append(" != ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 != val2;

}