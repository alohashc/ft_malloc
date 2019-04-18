//
// Created by aloha on 17.04.19.
//

#include "ft_malloc_lib.h"


void *first_zone_init(t_zone *zone, size_t size, int type)
{
    zone = MMAP(zone, PAGE_SIZE + size);

    if (MAP_FAILED == zone)
        return (NULL);
    zone->type = type;
    zone->size = size;
    zone->begin = (void*)zone + sizeof(t_zone);
    zone->address = zone;
    zone->next = NULL;
    zone->prev = NULL;

    return (zone);
}


void *getOptimalSize(size_t size, t_zone *block)
{
    size_t optimal_size = 0;
    int type = 0;

    if (size  <= TINY_BYTES)
    {
        type = TINY;
        optimal_size = TINY_BYTES * 100 + sizeof(t_zone);
    }
    if (size <= SMALL_BYTES)
    {
        type = SMALL;
        optimal_size = SMALL_BYTES * 100 + sizeof(t_zone);
    }
    if (size > SMALL_BYTES)
    {
        type = LARGE;
        optimal_size = size + sizeof(t_zone);
    }
    if (optimal_size % PAGE_SIZE)
        optimal_size += PAGE_SIZE - (optimal_size % PAGE_SIZE);
    block = first_zone_init(block, optimal_size, type);
    return (block);
}

void first_block_init(t_zone *zone, size_t size)
{
    zone->begin->next = NULL;
    zone->begin->is_available = 1;
    zone->begin->size = size;
    zone->begin->address = zone->begin + sizeof(t_block);
}

t_zone *extend_memory(size_t size)
{
    t_zone *zone;

    zone = (t_zone*)start_address;
    if (zone == NULL)
    {
        zone = getOptimalSize(size, zone);
        start_address = zone;
        first_block_init(zone, size);
    }
    return zone;
}

t_zone *find_zone(t_zone *begin, size_t size)
{
    t_zone *curr_zone;

    curr_zone = begin;
    while (curr_zone != NULL)
    {

    }
}


t_block *get_block(t_zone *zone, size_t size)
{
    t_zone *curr_zone;

    curr_zone = zone;
//    while (curr_zone->begin == NULL)
//    {
//        curr_zone
//    }
}

void *malloc(size_t size)
{
    t_zone *new_mem_location;
    t_block *block;

    if (!size)
        return NULL;
    new_mem_location = extend_memory(size);
    if (new_mem_location == NULL)
        return (NULL);
    block = get_block(new_mem_location, size); // TODO HERE ARE DIFFERENT BLOCK ADRESSES
    return NULL;
}
