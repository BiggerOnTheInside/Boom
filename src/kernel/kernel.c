/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#include <system.h>
#include <system/multiboot.h>
#include <system/filesystem/vfs/vfs.h>
#include <system/filesystem/initrd/initrd.h>
#include <colors.h>
#include <elf.h>

extern u32int end, placement_address;
extern initrd_header_t *initrd_header;

void kernel(struct multiboot *mboot_ptr)
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    initialise_paging();
    init_video();
    keyboard_install();
    timer_install();
    
    // And this inside a function
        
    __asm__ __volatile__ ("sti");
    
    settextcolor(WHITE, BLUE);

    puts("Now starting 'Yoda' OS, Pre-Alpha 0.0.2. Copyright 2015 Walt Pach, all rights reserved.\n\n");
    
    PRINT("Setting up system boot information...");
    
    DEBUG("Checking multiboot header...");
    ASSERT(mboot_ptr->mods_count > 0);
    DEBUG("Multiboot header successfuly checked.");
    
    
    DEBUG("Allocating memory for Initial Ramdisk location object...");
    u32int initrd_location = mboot_ptr->mods_addr;//malloc(sizeof(mboot_ptr->mods_addr));
    DEBUG_HEX("Memory allocation successful. Location = ", initrd_location);
    
    DEBUG("Allocating memory for Initial Ramdisk end location object...");
    u32int initrd_end = mboot_ptr->mods_addr+4;//malloc(sizeof(mboot_ptr->mods_addr + 4));
    DEBUG_HEX("Memory allocation successful. End location = ", initrd_end);

   // initrd_location = mboot_ptr->mods_addr;
    DEBUG_HEX("Initial Ramdisk location (from multiboot) = ", initrd_location);
    
    //initrd_end = mboot_ptr->mods_addr+4;
    DEBUG_HEX("Initial Ramdisk end location (from algorithm) = ", initrd_end);
    
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;
    DEBUG_HEX("Placement address = ", initrd_end);
    
    //initialise_paging();
    
    PRINT("Initialising filesystem root...");
    fs_root = initialise_initrd(initrd_location);
    PRINT("Done initialising filesystem root.");
    
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

