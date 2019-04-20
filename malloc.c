//
// Created by aloha on 17.04.19.
//

#include "ft_malloc_lib.h"


void *init_zone(t_zone *zone, size_t size, int type)
{
    zone = MMAP(zone, PAGE_SIZE + size);

    if (MAP_FAILED == zone)
        return (NULL);
    zone->type = type;
    zone->size = size;
    zone->available_space = size;
    zone->blocks = (void*)zone + sizeof(t_zone);
    zone->address = (void *)zone;
    zone->next = NULL;
    zone->prev = NULL;
    return (zone);
}

t_zone *getOptimalSize(size_t size, t_zone *block)
{
    size_t optimal_size = 0;
    int type = 0;

    if (size  <= TINY_BYTES)
    {
        type = TINY;
        optimal_size = TINY_BYTES * ALLOC + sizeof(t_zone);
    }
    if (size > TINY_BYTES && size <= SMALL_BYTES)
    {
        type = SMALL;
        optimal_size = SMALL_BYTES * ALLOC + sizeof(t_zone);
    }
    if (size > SMALL_BYTES)
    {
        type = LARGE;
        optimal_size = size + sizeof(t_zone);
    }
    if (optimal_size % PAGE_SIZE)
        optimal_size += PAGE_SIZE - (optimal_size % PAGE_SIZE);
    block = init_zone(block, optimal_size, type);
    return (block);
}

t_block *init_first_block(void *address, size_t size)
{
    t_block *new_block;

//    ft_bzero(address, sizeof(t_block));
    new_block = (t_block*)address;
    new_block->size = size;
    new_block->address = address;
    new_block->next = NULL;

    return (new_block);
}

t_block *new_block_init(t_zone *zone, size_t size)
{
    t_block *block = NULL;
    t_block *res = NULL;

    if (zone->blocks != NULL)
    {
        block = zone->blocks;
        while (block->next != NULL)
            block = block->next;
        res = init_first_block(block->address + block->size + sizeof(t_block), size);
        block->next = res;
    }
    return res;
}

t_zone *is_valid_zone(t_zone *zone, size_t  size)
{
    t_zone *curr_zone;
    int     type = 0;

    if (size <= TINY_BYTES)
        type = 0;
    else if (size <= SMALL_BYTES)
        type = 1;
    else if (size > SMALL_BYTES)
        type = 2;
    curr_zone = zone;
    while (curr_zone != NULL)
    {
        if (curr_zone->available_space >= size + sizeof(t_block) && curr_zone->type == type)
        {
            curr_zone->available_space = zone->available_space - sizeof(t_zone) - size;
            return (curr_zone);
        }
        curr_zone = curr_zone->next;
    }
    return curr_zone;
}

t_block *add_zone(t_zone *zone, size_t size)
{
    t_zone *curr_zone;

    curr_zone = zone;
    while (curr_zone->next != NULL)
    {
        curr_zone = curr_zone->next;
    }
    curr_zone->next = getOptimalSize(size, curr_zone->next);
    curr_zone = curr_zone->next;
    curr_zone->blocks = init_first_block(curr_zone->blocks, size);

    return curr_zone->blocks;
}

t_block *add_block(t_zone *zone, size_t size)
{
    t_zone *valid_zone;
    t_block *block = NULL;

    valid_zone = is_valid_zone(zone, size);
    if (valid_zone == NULL)
    {
        block = add_zone(zone, size);
    }
    if (valid_zone != NULL)
    {
        block = new_block_init(valid_zone, size);
    }
    return (block);
}

t_block *extend_memory(size_t size)
{
    t_zone *zone;
    t_block *block;

    zone = (t_zone*)start_address;
    if (zone == NULL)
    {
        zone = getOptimalSize(size, zone);
        start_address = zone;
        zone->available_space = zone->size - sizeof(t_zone) - size;
        block = init_first_block(zone->blocks, size);
    }
    else
    {
        block = add_block(zone, size);
    }
    return block;
}


void *malloc(size_t size)
{
    t_block *block;
    block = NULL;

    if (!size)
        return NULL;
    block = extend_memory(size);
    if (block == NULL)
        return (NULL);
    return (block->address + sizeof(t_block));
}
