//
// Created by aloha on 17.04.19.
//

#include "ft_malloc_lib.h"

t_zone *heap = NULL;
void    *last_valid_address;


void malloc_init()
{
    t_zone  *new_block;
}

void *malloc(size_t size)
{
    if (!size)
        return NULL;
    if (!heap)
    {
        MMAP(heap, size);
    }
}
