#ifndef SYSCALLS_H
#define SYSCALLS_H

#define STDOUT 1
#define STDERR 2

extern void write(int fd, char * buff );
extern void writeAt(int fd, char * buff, unsigned int pos);



#endif