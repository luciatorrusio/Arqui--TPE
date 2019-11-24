#include <deviceInfo.h>
#include <Curses.h>


void getRegisters(Registers * reg,uint64_t * stackPointer,uint64_t * instructionPointer){
   // printf("Agarrando a los registros\n");
   
    reg->rax = *(stackPointer+14);
//        printf("RAX: %d\n",reg->rax);
    reg->rbx = *(stackPointer+13);
//        printf("RBX: %d\n",reg->rbx);
    reg->rcx = *(stackPointer+12);
//        printf("RCX: %d\n",reg->rcx);

    reg->rdx = *(stackPointer+11);
//        printf("RdX: %d\n",reg->rdx);

    reg->rbp = *(stackPointer+10);
//        printf("Rbp: %d\n",reg->rbp);

    reg->rdi = *(stackPointer+9);
//        printf("Rdi: %d\n",reg->rdi);

    reg->rsi = *(stackPointer+8);
//        printf("Rsi: %d\n",reg->rsi);

    reg -> r8 = *(stackPointer+7);
 //       printf("R8: %d\n",reg->r8);

    reg -> r9 = *(stackPointer+6);
//        printf("R9: %d\n",reg->r9);

    reg->r10 = *(stackPointer+5);
//        printf("R10: %d\n",reg->r10);

    reg->r11 = *(stackPointer+4);
//        printf("R11: %d\n",reg->r11);

    reg->r12 = *(stackPointer+3);
//        printf("R12: %d\n",reg->r12);

    reg->r13 = *(stackPointer+2);
//        printf("R13: %d\n",reg->r13);

    reg->r14 = *(stackPointer+1);
//        printf("R14: %d\n",reg->r14);

    reg->r15 = *(stackPointer);
//        printf("R15: %d\n",reg->r15);


    reg->rip = instructionPointer;
//        printf("RIP: %d\n",reg->rip);


}

void readMem(uint64_t position, char * buff, unsigned size){

    char * memory = (char *) position;

    for (int i = 0; i < size; i++)
        buff[i] = memory[i];
    
}