/*************************************************************************/
/* Copyright 2015 Bigger On The Inside Development, all rights reserved. */
/*************************************************************************/

#include <types.h>
#include <string.h>

size_t strlen(const char *str)
{
    size_t retval;
    
    for(retval = 0; *str != '\0'; str++) retval++;
    
    return retval;
}


