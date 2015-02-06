/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#include <system.h>

void kernel()
{
    int i;
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    initialise_paging();
    init_video();
    timer_install();
   //// keyboard_install();
   //paging_init();
    
    // And this inside a function
        
    __asm__ __volatile__ ("sti");
    
    puts("Hello World!\n");
    
    //    i = 10 / 0;
    //    putch(i);
    
    char a = '1';
    char *b = malloc(sizeof(a));
    *b = a;
    char c = b;
    
    putch(c);
    
 
    return;
}


