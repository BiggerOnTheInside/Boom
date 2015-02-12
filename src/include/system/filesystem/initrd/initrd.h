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

typedef struct
{
    u32int nfiles; // The number of files in the ramdisk.
} initrd_header_t;

typedef struct
{
    u8int magic;     // Magic number, for error checking.
    s8int name[64];  // Filename.
    u32int offset;   // Offset in the initrd that the file starts.
    u32int length;   // Length of the file.
} initrd_file_header_t;

// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
// and returns a completed filesystem node.
fs_node_t *initialise_initrd(u32int location);
#endif