/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#ifndef __SYSTEM_IRQ_H
    #define __SYSTEM_IRQ_H

    extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
    extern void irq_uninstall_handler(int irq);
    extern void irq_install();
#endif