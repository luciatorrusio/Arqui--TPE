#include "include/Commands.h"

#include "../Include/deviceInfo.h"
#include "../Include/String.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"

int printMem(uint64_t memDirection){

    char rawMem[32];
    readMem(memDirection,rawMem,32);
    
    char printStr[(16 * 3) + 1];

    printf("Reading Memory: \n");

    for(int j=0 ; j <2 ; j++){
        for(int i = 0 ; i < 16 ; i++){
            HexToString(printStr + i*3,3,rawMem[16 * j +i]);
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

/* Cuando este el printf lo terminamos
    char arr[200];
    char month[10];
    cleanArr(arr,200);

    IntToString(month,10,GetMonth());
    append("Month: ",arr,200);

    append(month,arr,200);

    printf(arr);
 */
 printf("%d/%d/%d %d:%d:%d \n",GetDayOfMonth(),GetMonth(),GetYear(),GetHours(),GetMinutes(),GetSeconds());   
    return 0;

}