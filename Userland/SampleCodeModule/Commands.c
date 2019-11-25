#include "include/Commands.h"

#include "../Include/deviceInfo.h"
#include "../Include/String.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"

extern void __executeCodeFromAddress__(void * address);

int quotient(int a, int b){

    printf("I'm going to calculate the quotient of %d divided by %d\n",a,b);

    int result =  (a)/ (b);
    
    printf("The result is %d\n",result);
    return 0;
}

int man(){
    printf("\ngame\nexit\ntime\nman\ninvalidOpcode\ninfoReg\nquotient\nprintMem\nclear\n");
    return 0;
}

int explainCommand(char * command){

    if(strcmp(command,"time")){
        printf("Command:\n        time\n");
        printf("It shows the current date and time.\n");
    }
    else if(strcmp(command,"man")){
        printf("Command:\n        man ?[Argument_1]\n");
        printf("It enumerates all the commands available on this shell\n");
        printf("If there's an argument, it will tell you the funcition of that command\n");
    }
    else if(strcmp(command,"infoReg")){
        printf("Command:\n        infoReg\n");
        printf("It prints on screen the actual value of the registers\n");
    }
    else if(strcmp(command,"printMem")){
        printf("Command:\n        printMem [Argument_1]\n");
        printf("It prints on screen the first 32 bytes of memory from any given memory position.\n");
    }
    else if(strcmp(command,"game")){
        printf("Command:\n        game\n");
        printf("It unpauses/starts the game arachnoid.\n");
    }
    else if(strcmp(command,"exit")){
        printf("Command:\n        exit\n");
        printf("It exits the program.\n");
    }
    else if(strcmp(command,"invalidOpcode")){
        printf("Command:\n        invalidOpcode\n");
        printf("It is a test to validate the INVALID OPCODE exception.\n");
    }
    else if(strcmp(command,"clear")){
        printf("Command:\n        clear\n");
        printf("It clears the screen.\n");
    }
    else if(strcmp(command,"quotient")){
        printf("Command:\n        quotient [Argument_1] [Argument_2]\n");
        printf("It calculates the quotient of the division of [Argument_1] by [Argument_2]. This can be used to test the DIVISION BY ZERO exception.\n");
    }else{
        printf("That command does not exist!\n");
    }

}

int invalidOpcode(){

    char * temp = "CRASH";

    __executeCodeFromAddress__(temp);

    return 0;
}

int printMem(uint64_t memDirection){

    char rawMem[32];
    readMem(memDirection,rawMem,32);
    
    char printStr[(16 * 3) + 1];

    for(int j=0 ; j <2 ; j++){
        for(int i = 0 ; i < 16 ; i++){
            HexToStringSPECIAL(printStr + i*3,3,rawMem[16 * j +i]);
            printStr[(i*3)-1] = ' ';
        }
        printf("%s\n",printStr);
    }

    return 0;

}


void cleanArr(char * arr, int size){
    for(int i = 0; i < size ; i++)
        arr[i] = 0;
}


int infoReg(){
    
    Registers reg;
    getRegisters(&reg);
    
    char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};    
    
    HexToString(temp,17,reg.rax);
	printf("RAX: 0x%s\n",temp);
    
    HexToString(temp,17,reg.rbx);
	printf("RBX: 0x%s\n",temp);
    
	HexToString(temp,17,reg.rcx);
	printf("RCX: 0x%s\n",temp);
    	
    HexToString(temp,17,reg.rdx);
	printf("RDX: 0x%s\n",temp);
    
    HexToString(temp,17,reg.rbp);
	printf("RBP: 0x%s\n",temp);


    HexToString(temp,17,reg.rsi);
	printf("RSI: 0x%s\n",temp);
    	
    HexToString(temp,17,reg.rdi);
	printf("RDI: 0x%s\n",temp);
    
    HexToString(temp,17,reg.r8);
	printf("R8: 0x%s\n",temp);	

    HexToString(temp,17,reg.r9);
	printf("R9: 0x%s\n",temp);	
	
    HexToString(temp,17,reg.r10);
	printf("R10: 0x%s\n",temp);	

    HexToString(temp,17,reg.r11);
	printf("R11: 0x%s\n",temp);	
	
    HexToString(temp,17,reg.r12);
	printf("R12: 0x%s\n",temp);	
	
	HexToString(temp,17,reg.r13);
	printf("R13: 0x%s\n",temp);	
	
    HexToString(temp,17,reg.r14);
	printf("R14: 0x%s\n",temp);	
	
    HexToString(temp,17,reg.r15);
	printf("R15: 0x%s\n",temp);	

    HexToString(temp,17,reg.rip);
	printf("RIP: 0x%s\n",temp);	
    return 0;

}

int time(){
    int dayofMonth = GetDayOfMonth();
    int month = GetMonth();
    int year = GetYear();
    int hour = GetHours();
    int minutes = GetMinutes();
    int seconds = GetSeconds();
    printf("%d/%d/%d %d:%d:%d \n",dayofMonth,month,year,hour, minutes,seconds);   
    return 0;

}