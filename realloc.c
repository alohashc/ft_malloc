//
// Created by aloha on 20.04.19.
//

#include "ft_malloc_lib.h"

t_block *find_block(void * address, size_t size)
{
    t_zone *curr_zone;
    t_block *curr_block;

    curr_block = NULL;
    curr_zone = (t_zone*)start_address;
    while (curr_zone)
    {
        curr_block = curr_zone->blocks;
        while (curr_block)
        {
            if (curr_block->address == address - sizeof(t_block))
                return (curr_block);
            curr_block = curr_block->next;
        }
        curr_zone = curr_zone->next;
    }
    return (curr_block);
}

void *reallocate(void *address, size_t size, size_t old_size)
{
    void *new;
    size_t min_size;

    min_size = old_size >= size ? size : old_size;
    new = malloc(size);
    if(new)
    {
        ft_memmove(new, address, min_size);
        free(address);
    }
    return (new);
}

void *realloc(void *ptr, size_t size)
{
    t_block *block;
    t_zone *zone;

    if (ptr == NULL)
        return (malloc(size));
    if (size == 0)
    {
        free(ptr);
        return (0);
    }
    block = find_block(ptr, size);
    zone = (t_zone*)block->zone;
    if (block->size + sizeof(t_block) >= size || (!block->next && is_space(zone, size)))
    {
        zone->available_space -= (sizeof(t_block) + size - block->size);
        block->size = size + sizeof(t_block);
        return (ptr);
    }
    return (reallocate(ptr, size, block->size));
}