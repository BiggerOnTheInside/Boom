#include <system.h>

#ifndef __SYSTEM_IO_H
    #define __SYSTEM_IO_H

    extern void *memcpy(void *dest, const void *src, size_t count);
    extern void *memset(void *dest, char val, size_t count);
    extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);

    extern u8int inportb(u16int port);
    extern void outportb (u16int port, u8int data);
    extern u16int inportword(u16int port);
#endif