/*
 *  gdt.h
 *  Boom
 *
 *  Created by Walt Pach on 2/5/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */


extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();
