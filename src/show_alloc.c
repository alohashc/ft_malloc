//
// Created by Andrii Lohashchuk on 2019-04-21.
//

#include "inc/ft_malloc_lib.h"


int display_blocks_info(t_block *block)
{
    char *address_start;
    char *address_end;
    int  total_bytes;

    total_bytes = 0;
    while (block)
    {
        address_start = ft_itoa_base((long)block->address, 16, 'A');
        address_end = ft_itoa_base((long)block->address + block->size, 16, 'A');
        ft_putstr("0x");
        ft_putstr(address_start);
        ft_putstr(" - ");
        ft_putstr("0x");
        ft_putstr(address_end);
        ft_putstr(" : ");
        ft_putnbr((int)block->size);
        ft_putendl(" bytes");
        ft_strdel(&address_start);
        ft_strdel(&address_end);
        total_bytes += block->size;
        block = block->next;
    }
    return (total_bytes);
}

void display_zone_info(t_zone *zone)
{
    char *address;

    address = NULL;
    if (zone->type == 0)
        ft_putstr("TINY : ");
    else if (zone->type == 1)
        ft_putstr("SMALL : ");
    else
        ft_putstr("LARGE : ");
    address = ft_itoa_base((long)zone->address, 16, 'A');
    ft_putstr("0x");
    ft_putendl(address);
    ft_strdel(&address);
}

void show_alloc_mem()
{
    t_zone *zone;
    t_block *block;
    int total_bytes;

    total_bytes = 0;
    zone = (t_zone*)g_zone;
    while (zone)
    {
        block = zone->blocks;
        display_zone_info(zone);
        total_bytes += display_blocks_info(block);
        zone = zone->next;
    }
    ft_putstr("Total : ");
    ft_putnbr(total_bytes);
    ft_putstr(" bytes");
}