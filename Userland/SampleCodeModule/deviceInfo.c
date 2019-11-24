#include "../Include/deviceInfo.h"
extern void __READMEM__(uint64_t position, char * buff, unsigned size);
extern void __GETREGISTERS__(void * reg);
extern void __GETBPP__(void * bpp);
extern void __SETBPP__(int bpp);
extern void __GETCHARH__(unsigned int * c);
extern void __GETCHARW__(unsigned int * c);

void getRegisters(Registers * reg){

    __GETREGISTERS__(reg);
}
void readMem(uint64_t position, char * buff, unsigned size){

    __READMEM__(position,buff,size);

}

void getBpp(unsigned int * bpp){

    __GETBPP__(bpp);

}

void setSize(unsigned int bpp){
    __SETBPP__(bpp);
}

void getCharHeight(unsigned int * c){
    __GETCHARH__(c);
}

void getCharWidth(unsigned int * c){
    __GETCHARW__(c);
}
