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
    zone->begin = (void*)zone + sizeof(t_zone);
    zone->address = (void *) zone + sizeof(t_zone);
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

    new_block = (t_block*)address;
    ft_bzero(address, sizeof(t_block));
    new_block->size = size;
    new_block->address = address + sizeof(t_block);
    block_address = new_block->address;
    new_block->next = NULL;

    return (new_block);
}

t_zone *new_block_init(t_zone *zone, size_t size)
{
    t_block *block;

    if (zone->begin != NULL)
    {
        block = zone->begin;
        while (block->next != NULL)
            block = block->next;
        block->next = (void*)block + size + sizeof(t_block);
        block->next = init_first_block(block->next, size);
    }
    zone_address = zone->address;
    return zone;
}

t_zone *is_valid_zone(t_zone *zone, size_t  size)
{
    t_zone *curr_zone;

    curr_zone = zone;
    while (curr_zone != NULL)
    {
        if (curr_zone->available_space >= size)
            return (curr_zone);
        curr_zone = curr_zone->next;
    }
    return curr_zone;
}

t_zone *add_zone(t_zone *zone, size_t size)
{
    t_zone *curr_zone;

    curr_zone = zone;
    while (curr_zone->next != NULL)
    {
        curr_zone = curr_zone->next;
    }
    curr_zone->next = getOptimalSize(size, curr_zone->next);
    curr_zone = curr_zone->next;
    curr_zone->begin = init_first_block(curr_zone->begin, size);

    return zone;
}

void add_block(t_zone *zone, size_t size)
{
    t_zone *valid_zone;

    zone->available_space = zone->available_space - sizeof(t_zone) - size;
    valid_zone = is_valid_zone(zone, size);
    if (valid_zone == NULL)
    {
        zone = add_zone(zone, size);
    }
    if (valid_zone != NULL)
    {
        zone = new_block_init(valid_zone, size);
    }
}

t_zone *extend_memory(size_t size)
{
    t_zone *zone;

    zone = (t_zone*)start_address;
    if (zone == NULL)
    {
        zone = getOptimalSize(size, zone);
        start_address = zone;
        zone->available_space = zone->size - sizeof(t_zone) - size;
        init_first_block(zone->begin, size);
    }
    else
        add_block(zone, size);
    return zone;
}

t_zone *find_zone(t_zone *begin, void *address)
{
    t_zone *curr_zone;

    curr_zone = begin;
    while (curr_zone != NULL)
    {
        if (curr_zone->address == address)
            return curr_zone;
        curr_zone = curr_zone->next;
    }
    return (curr_zone);
}


//t_block *get_block(t_zone *zone, void *block_address, void* zone_address)
//{
//    t_zone *curr_zone;
//
//    curr_zone = zone;
//    while (curr_zone->begin == NULL)
//    {
//        curr_zone = find_zone(zone, zone_address);
//        if (curr_zone != NULL)
//        {
//            curr_zone->begin
//        }
//    }
//}

void *malloc(size_t size)
{
    t_zone *new_mem_location;
    t_block *block;

    if (!size)
        return NULL;
    new_mem_location = extend_memory(size);
    if (new_mem_location == NULL)
        return (NULL);
//    block = get_block(new_mem_location, block_address, zone_address); // TODO HERE ARE DIFFERENT BLOCK ADRESSES
    return block_address;
}
