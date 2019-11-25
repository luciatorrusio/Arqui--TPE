#include "../Include/deviceInfo.h"
#include "../include/Syscalls.h"

extern void __GETREGISTERS__(void * reg);


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
    __GETSCREENW__(s);
}

void getScreenHeight(unsigned int * s){
    __GETSCREENH__(s);
}