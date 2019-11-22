#include "include/Speaker.h"
#include "../include/Syscalls.h"

#define FD_SPEAKER (3)

void beep(){

    write(FD_SPEAKER,0);

}