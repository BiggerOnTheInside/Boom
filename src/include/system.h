/* bkerndev - Bran's Kernel Development Tutorial
 *  By:   Brandon F. (friesenb@gmail.com)
 *  Desc: Global function declarations and type definitions
 *
 *  Notes: No warranty expressed or implied. Use at own risk. */
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <types.h>
#include <string.h>

#include <system/irq.h>
#include <system/isrs.h>
#include <system/idt.h>
#include <system/gdt.h>
#include <system/io.h>
#include <system/memory.h>
#include <system/kheap.h>
#include <system/paging.h>

#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <drivers/screen.h>

#endif
