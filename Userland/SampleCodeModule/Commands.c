#include "include/Commands.h"

#include "../Include/deviceInfo.h"
#include "../Include/String.h"
#include "Include/Terminal.h"
#include "../Include/Time.h"

int printMem(uint64_t memDirection){

    char rawMem[32];
    readMem(memDirection,rawMem,32);
    
    char printStr[(16 * 3) + 1];

    writeLineToTerminal("Reading Memory: ");

    for(int j=0 ; j <2 ; j++){
        for(int i = 0 ; i < 16 ; i++){
            HexToString(printStr + i*3,3,rawMem[16 * j +i]);
            printStr[(i*3)-1] = ' ';
        }
        writeLineToTerminal(printStr);
    }

    return 0;

}


void cleanArr(char * arr, int size){
    for(int i = 0; i < size ; i++)
        arr[i] = 0;
}


int infoReg(){
    Registers reg = getRegisters();

    char temp[17]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',0};

    char arr[200];

    cleanArr(arr,200);
    append("RAX: 0X",arr,200);
    HexToString(temp,17,reg.rax);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);


	
    cleanArr(arr,200);
    append("RBX: 0X",arr,200);
    HexToString(temp,17,reg.rbx);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);

	
    cleanArr(arr,200);
    append("RCX: 0X",arr,200);
    HexToString(temp,17,reg.rcx);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);

	
    cleanArr(arr,200);
    append("RDX: 0X",arr,200);
    HexToString(temp,17,reg.rdx);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("RSI: 0X",arr,200);
    HexToString(temp,17,reg.rsi);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("RDI: 0X",arr,200);
    HexToString(temp,17,reg.rdi);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R8:  0X",arr,200);
    HexToString(temp,17,reg.r8);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R9:  0X",arr,200);
    HexToString(temp,17,reg.r9);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R10: 0X",arr,200);
    HexToString(temp,17,reg.r10);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R11: 0X",arr,200);
    HexToString(temp,17,reg.r11);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R12: 0X",arr,200);
    HexToString(temp,17,reg.r12);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R13: 0X",arr,200);
    HexToString(temp,17,reg.r13);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R14: 0X",arr,200);
    HexToString(temp,17,reg.r14);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);
	

    cleanArr(arr,200);
    append("R15: 0X",arr,200);
    HexToString(temp,17,reg.r15);
	append(temp,arr,200);
    
	writeLineToTerminal(arr);

    return 0;

}

int time(){

// Cuando este el printf lo terminamos
    char arr[200];
    char month[10];
    cleanArr(arr,200);

    IntToString(month,10,GetMonth());
    append("Month: ",arr,200);

    append(month,arr,200);

    writeLineToTerminal(arr);
    
    return 0;

}