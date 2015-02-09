/*
 *  initrd.h
 *  Boom
 *
 *  Created by Walt Pach on 2/9/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SYSTEM_INITRD_H
#define __SYSTEM_INITRD_H

#include <system.h>
#include <system/filesystem/vfs/vfs.h>

typedef struct{
    u32int nfiles;
} initrd_header_t

typedef struct{
    u8int magic;
    s8int name[64];
    u32int offset;
    u32int length;
} initrd_file_header_t;

fs_node_t *initialise_initrd(u32int location);

#endif