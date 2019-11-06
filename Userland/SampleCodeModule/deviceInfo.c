#include "../include/deviceInfo.h"

extern void __READMEM__(uint64_t position, char * buff, unsigned size);
extern void __GETREGISTERS__(void * reg);

Registers getRegisters(){

    Registers reg;

    __GETREGISTERS__(&reg);

    return reg;
}
void readMem(uint64_t position, char * buff, unsigned size){

    __READMEM__(position,buff,size);

}