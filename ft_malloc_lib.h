#ifndef MALLOC_FT_MALLOC_LIB_H
#define MALLOC_FT_MALLOC_LIB_H

#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft/libft.h"

#define MMAP(ptr, size) mmap((ptr), (size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#define OFFSET_BLOCK sizeof(struct t_zone)
#define TINY 0
#define SMALL 1
#define LARGE 2
#define TINY_BYTES 1024
#define SMALL_BYTES 1024 * 16
#define ALLOC 2

typedef struct s_block
{
    size_t  size;
    void    *address;
    struct s_block *next;
    struct s_block *prev;
    int is_available;

}               t_block;

typedef struct s_zone
{
    int type;
    size_t size;
    size_t available_space;
    t_block  *begin;

    struct s_zone *next;
    struct s_zone *prev;
    void    *address;

}               t_zone;

void *start_address;
void *block_address;
void *zone_address;


void *malloc(size_t);
t_zone *extend_memory(size_t size);
t_zone *find_zone(t_zone *begin, void *address);

#endif //MALLOC_FT_MALLOC_LIB_H