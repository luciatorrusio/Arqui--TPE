#include "../Include/deviceInfo.h"
#include "../include/Syscalls.h"

extern void __READMEM__(uint64_t position, char * buff, unsigned size);
extern void __GETREGISTERS__(void * reg);
extern void __GETBPP__(void * bpp);
extern void __SETBPP__(int bpp);
extern void __GETCHARH__(unsigned int * c);
extern void __GETCHARW__(unsigned int * c);

typedef struct{
    unsigned int bbp;
    unsigned int charHeight;
    unsigned int charWidht;
    unsigned int screenHeight;
    unsigned int screenWidth;
}DeviceInfo;


void getRegisters(Registers * reg){

    // NO PUEDO CAMBIER ESTO POR UN READ POR LA FORMA EN LA QUE AGARRO EL STACKPOINTER
    __GETREGISTERS__(reg);
}
void readMem(uint64_t position, char * buff, int size){

    read(FD_MEMORY,position,buff,size,0);
    // __READMEM__(position,buff,size);

}

void getBpp(unsigned int * bpp){

    DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *bpp = temp.bbp;

    // __GETBPP__(bpp);

}

void setSize(unsigned int bpp){
    write(FD_DEVICE_INFO,bpp,0,0,0);
    __SETBPP__(bpp);
}

void getCharHeight(unsigned int * c){
     DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *c = temp.charHeight;
    // __GETCHARH__(c);
}

void getCharWidth(unsigned int * c){
     DeviceInfo temp;

    read(FD_DEVICE_INFO,&temp,0,0,0);

    *c = temp.charWidht;
    // __GETCHARW__(c);
}
