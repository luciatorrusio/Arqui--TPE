#ifndef SYSCALLS_H
#define SYSCALLS_H

#define STDOUT 1
#define STDERR 2

extern void write(int fd, char * buff );

extern void read(int fd,char * buff, unsigned int size);

extern void delete(int fd);
extern void printAt(int *pos ,int lenght,int height,int fontColor);



#endif