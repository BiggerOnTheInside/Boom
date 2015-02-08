/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <types.h>
#include <string.h>

#include <system/irq.h>
#include <system/isrs.h>
#include <system/idt.h>
#include <system/gdt.h>
#include <system/io.h>
#include <system/ordered_array.h>
#include <system/memory.h>
#include <system/kheap.h>
#include <system/paging.h>

#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <drivers/screen.h>


extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);

#endif
