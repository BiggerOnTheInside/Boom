/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#include <system.h>
#include <system/multiboot.h>
#include <system/filesystem/vfs/vfs.h>
#include <system/filesystem/initrd/initrd.h>

extern u32int end, placement_address;

void kernel(struct multiboot *mboot_ptr)
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    // And this inside a function
        
    __asm__ __volatile__ ("sti");
    
    
    ASSERT(mboot_ptr->mods_count > 0);
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;
    
    initialise_paging();
    init_video();
    keyboard_install();
    timer_install();

    fs_root = initialise_initrd(initrd_location);
    
    int i = 0;
    struct dirent *node = 0;
    while ( (node = readdir_fs(fs_root, i)) != 0)
    {
        puts("Found file ");
        puts(node->name);
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);
        
        if ((fsnode->flags&0x7) == FS_DIRECTORY)
            puts("\n\t(directory)\n");
        else
        {
            puts("\n\t contents: \"");
            char buf[256];
            u32int sz = read_fs(fsnode, 0, 256, buf);
            int j;
            for (j = 0; j < sz; j++)
                putch(buf[j]);
            
            puts("\"\n");
        }
        i++;
    }
    return;
}


