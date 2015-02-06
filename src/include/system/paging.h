/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/
#include <system.h>

u32int page_directory[1024] __attribute__((alligned(4096)));
u32int first_page_table[1024] __attribute__((alligned(4096)));

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();
extern void paging_init();