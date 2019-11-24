#ifndef SYSCALLS_H
#define SYSCALLS_H

#define STDOUT 1
#define STDERR 2

#define FD_STDOUT_COLOR (0xB)

typedef struct{
    char ch;
    int fontColor;
    int backgroundColor;
    int x;
    int y;
}ColorChar;

extern void write(int fd, void * first, void *second, void * third, void * forth );

extern void read(int fd,char * buff, unsigned int size);

extern void delete(int fd);
extern void printAt(int *pos ,int lenght,int height,int fontColor);

extern void writeColor(ColorChar * buff );

#endif