/*
 *  irq.h
 *  Boom
 *
 *  Created by Walt Pach on 2/5/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SYSTEM_IRQ_H
    #define __SYSTEM_IRQ_H

    extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
    extern void irq_uninstall_handler(int irq);
    extern void irq_install();
#endif