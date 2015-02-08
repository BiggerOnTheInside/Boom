/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/
#ifndef __SYSTEM_IDT_H
    #define __SYSTEM_IDT_H
    extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
    extern void idt_install();
#endif