//
// Created by Andrii Lohashchuk on 2019-04-20.
//

#include "inc/ft_malloc_lib.h"


void deallocate(t_block *del, t_zone *zone)
{
    t_block *prev;
    t_block *next;
    t_block *curr;

    prev = NULL;
    curr = zone->blocks;
    while (curr)
    {
        if (curr == del)
        {
            if (prev)
                prev->next = del->next;
            else
                zone->blocks = del->next;

        }
        prev = curr;
        curr = curr->next;
    }
}

void delete_zone(t_zone *del)
{
    t_zone *prev;
    t_zone *curr;

    prev = NULL;
    curr = g_zone;
    while (curr != NULL)
    {
        if (del == curr)
        {
            if (!prev)
                g_zone = curr->next;
            else
                prev->next = curr->next;
            munmap(del, del->size);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

void free(void *ptr)
{
    t_zone *curr_zone;
    t_block *curr_block;
    t_zone *prev;

    prev = NULL;
    curr_zone = (t_zone*)g_zone;
    if (ptr != NULL && g_zone != NULL)
    {
        while (curr_zone != NULL)
        {
            curr_block = curr_zone->blocks;
            while (curr_block != NULL && curr_block->address != ptr - sizeof(t_block)) {
                curr_block = curr_block->next;
            }
            if (curr_block)
            {
                deallocate(curr_block, curr_zone);
                curr_zone->available_space += curr_block->size + sizeof(t_zone);
                if (curr_zone->size == curr_zone->available_space)
                {
                    if (prev)
                        prev = curr_zone->next;
                    else
                        g_zone = curr_zone->next;
                    delete_zone(curr_zone);
                    break;
                }
            }
            prev = curr_zone;
            curr_zone = curr_zone->next;
        }
    }
}