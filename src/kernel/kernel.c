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
    ide_initialize(0x1F0, 0x3F4, 0x170, 0x374, 0x000);
    
    char a = 'W';
    char *ptr = kmalloc(sizeof(char));
    u32int *pt = kmalloc(sizeof(u32int));
    
    puts_hex(ptr);
    putch('\n');
    puts_hex(pt);
    
    kfree(ptr);
    
    
    return;
}


