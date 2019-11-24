#ifndef SYSCALLS_H
#define SYSCALLS_H

#define STDOUT 1
#define STDERR 2

typedef struct{
    char ch;
    int fontColor;
    int backgroundColor;
    int x;
    int y;
}ColorChar;

extern void write(int fd, char * buff );

extern void read(int fd,char * buff, unsigned int size);

extern void delete(int fd);

extern void writeColor(ColorChar * buff );

#endif