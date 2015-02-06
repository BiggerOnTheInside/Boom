/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/
#include <system.h>

#ifndef KHEAP_H
    #define KHEAP_H

    /**
     Allocate a chunk of memory, sz in size. If align == 1,
     the chunk must be page-aligned. If phys != 0, the physical
     location of the allocated chunk will be stored into phys.
 
     This is the internal version of kmalloc. More user-friendly
     parameter representations are available in kmalloc, kmalloc_a,
     kmalloc_ap, kmalloc_p.
    **/
    u32int malloc_int(u32int sz, int align, u32int *phys);

    /**
     Allocate a chunk of memory, sz in size. The chunk must be
     page aligned.
    **/
    u32int malloc_a(u32int sz);

    /**
     Allocate a chunk of memory, sz in size. The physical address
     is returned in phys. Phys MUST be a valid pointer to u32int!
    **/
    u32int malloc_p(u32int sz, u32int *phys);

    /**
     Allocate a chunk of memory, sz in size. The physical address 
     is returned in phys. It must be page-aligned.
    **/
    u32int malloc_ap(u32int sz, u32int *phys);

    /**
     General allocation function.
    **/
    u32int malloc(u32int sz);

#endif // KHEAP_H
