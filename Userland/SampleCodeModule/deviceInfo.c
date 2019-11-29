#include "../Include/deviceInfo.h"
#include "../Include/Syscalls.h"

// extern void __GETREGISTERS__(void * reg);


typedef struct{
    unsigned int bbp;
    unsigned int charHeight;
    unsigned int charWidht;
    unsigned int screenHeight;
    unsigned int screenWidth;
}DeviceInfo;


void recoverRegisters(uint64_t * stackPointer){

    Registers structure;
    //  push ebp
    //  mov ebp, esp
    structure.r15 = *(stackPointer + 0);    
    structure.r14 = *(stackPointer + 1);
    structure.r13 = *(stackPointer + 2);
    structure.r12 = *(stackPointer + 3);
    structure.r11 = *(stackPointer + 4);
    structure.r10 = *(stackPointer + 5);
    structure.r9 = *(stackPointer + 6);
    structure.r8 = *(stackPointer + 7);
    structure.rsi = *(stackPointer + 8);
    structure.rdi = *(stackPointer + 9);

    // Cuando entra a la funcion me guarda en el rbp la posicion del stackpointer antes de entrar 
    // a la funcion.
    structure.rsp = *(stackPointer + 10);

    structure.rdx = *(stackPointer + 11);
    structure.rcx = *(stackPointer + 12);
    structure.rbx = *(stackPointer + 13);
    structure.rax = *(stackPointer + 14);

    // Al armar el stack frame pusheo al stack el valor del rbp.
    structure.rbp = *(stackPointer + 15);

    return structure;


}


// void getRegisters(Registers * reg){

//     __GETREGISTERS__(reg);
// }
void readMem(uint64_t position, char * buff, int size){

    read(FD_MEMORY,position,buff,size,0);

}

void getBpp(unsigned int * bpp){

    DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *bpp = temp.bbp;

}

void setSize(unsigned int bpp){
    write(FD_DEVICE_INFO,bpp,0,0,0);
}

void getCharHeight(unsigned int * c){
     DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *c = temp.charHeight;
}

void getCharWidth(unsigned int * c){
     DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *c = temp.charWidht;
}

void getScreenWidth(unsigned int * s){

         DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *s = temp.screenWidth;
    
}

void getScreenHeight(unsigned int * s){

         DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *s = temp.screenHeight;

}