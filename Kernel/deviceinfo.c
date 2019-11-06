#include <deviceInfo.h>

extern uint64_t raxRegister();
extern uint64_t rbxRegister();
extern uint64_t rcxRegister();
extern uint64_t rdxRegister();
extern uint64_t rdiRegister();
extern uint64_t rsiRegister();
extern uint64_t r8Register();
extern uint64_t r9Register();
extern uint64_t r10Register();
extern uint64_t r11Register();
extern uint64_t r12Register();
extern uint64_t r13Register();
extern uint64_t r14Register();
extern uint64_t r15Register();
extern uint64_t ipRegister();



Registers getRegisters(){
    Registers reg;

    reg.rax = raxRegister();
    reg.rbx = rbxRegister();
    reg.rcx = rcxRegister();
    reg.rdx = rdxRegister();
    reg.rip = ipRegister();
    reg.rdi = rdiRegister();
    reg.rsi = rsiRegister();
    reg.r8 = r8Register();
    reg.r9 = r9Register();
    reg.r10 = r10Register();
    reg.r11 = r11Register();
    reg.r12 = r12Register();
    reg.r13 = r13Register();
    reg.r14 = r14Register();
    reg.r15 = r15Register();


    return reg;

}

void readMem(uint64_t position, char * buff, unsigned size){

    char * memory = (char *) position;

    for (int i = 0; i < size; i++)
        buff[i] = memory[i];
    
}