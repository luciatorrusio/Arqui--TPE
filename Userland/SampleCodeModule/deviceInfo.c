#include "../Include/deviceInfo.h"
extern void __READMEM__(uint64_t position, char * buff, unsigned size);
extern void __GETREGISTERS__(void * reg);

void getRegisters(Registers * reg){

    __GETREGISTERS__(reg);
}
void readMem(uint64_t position, char * buff, unsigned size){

    __READMEM__(position,buff,size);

}