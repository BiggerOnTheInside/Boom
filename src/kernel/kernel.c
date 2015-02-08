/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#include <system.h>

extern u32int end;

void kernel()
{
    int i;
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    initialise_paging();
    init_video();
    keyboard_install();
    timer_install();
    
    // And this inside a function
        
    __asm__ __volatile__ ("sti");
    
    puts("Hello World!\n");
    
    //    i = 10 / 0;
    //    putch(i);
    puts("Just testing the paging, and heap stuff :)\n\n\n");
    
    puts("Mapped memory: ");
    puts_hex(end);
 
    u32int *ptr = (u32int*)0xfffffffffffffffffffffffff;
    u32int a = *ptr;
    return;
}


