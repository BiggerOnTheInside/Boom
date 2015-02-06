/*
 *  idt.h
 *  Boom
 *
 *  Created by Walt Pach on 2/5/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();