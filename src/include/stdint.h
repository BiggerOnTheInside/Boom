/*
 *  stdint.h
 *  Boom
 *
 *  Created by Walt Pach on 2/10/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __LIB_STDINT_H
    #define __LIB_STDINT_H
    
    typedef int size_t;
    typedef unsigned int    u32int;
    typedef          int    s32int;
    typedef unsigned short  u16int;
    typedef          short  s16int;
    typedef unsigned char   u8int;
    typedef          char   s8int;
    
    typedef          char   boolean;
    typedef          char   byte;
    typedef          u16int Elf32_Half;     // Unsigned half int
    typedef          u32int Elf32_Off;      // Unsigned offset
    typedef          u32int Elf32_Addr;     // Unsigned address
    typedef          u32int Elf32_Word;     // Unsigned int
    typedef          s32int Elf32_Sword;	// Signed int
#endif