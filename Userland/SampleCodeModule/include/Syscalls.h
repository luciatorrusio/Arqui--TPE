#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdlib.h>

#define FD_STDOUT 				(0x01)
#define FD_STDERR 				(0x02)
#define FD_STDIN 				(0x03)

#define FD_SQUARES 				(0x05)
#define FD_MEMORY 				(0x06)
#define FD_REGISTERS			(0x07)
#define FD_DEVICE_INFO  		(0x08)
#define FD_TIMER				(0x09)
#define FD_TIME					(0x0A)
#define FD_STDOUT_COLOR			(0x0B)
#define FD_BORDER 				(0x0C)
#define FD_HIGHLIGHT            (0x0D)
#define FD_PIECE                (0x0E)

#define DELETE_CURRENT_CHAR 1
#define DELETE_ALL_DISPLAY 3

extern void write(int fd, void * first, void *second, void * third, void * forth );

extern void read(int fd, void * first, void *second, void * third, void * forth);

extern void delete(int fd, void * first, void *second, void * third, void * forth);

#endif