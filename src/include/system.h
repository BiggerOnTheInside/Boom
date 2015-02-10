/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <colors.h>

#define PRINT(message) putch('['); puts(__FUNCTION__); putch(']'); putch(' '); puts(message); putch('\n');
#define PRINT_HEX(message, hex) putch('['); puts(__FUNCTION__); putch(']'); putch(' '); puts(message); puts_hex(hex); putch('\n');
#define PRINT_DEC(message, dec) putch('['); puts(__FUNCTION__); putch(']'); putch(' '); puts(message); puts_decimal(dec); putch('\n');
#define ERROR(message) clear(); puts("[ERROR - "); puts(__FUNCTION__); putch(']'); putch(' '); puts(message); putch('\n'); for(;;);
#define DEBUG(message) debug(message);
#define DEBUG_HEX(message, hex) debug(message, hex);
#define DEBUG_DEC(message, dec) debug(message, dec);

#define true 1
#define false 0

#include <types.h>
#include <string.h>

#include <system/irq.h>
#include <system/isrs.h>
#include <system/idt.h>
#include <system/gdt.h>
#include <system/io.h>
#include <system/memory/ordered_array.h>
#include <system/memory/memory.h>
#include <system/memory/kheap.h>
#include <system/memory/paging.h>

#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <drivers/screen.h>

extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);

#endif
