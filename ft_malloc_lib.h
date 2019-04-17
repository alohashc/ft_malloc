#ifndef MALLOC_FT_MALLOC_LIB_H
#define MALLOC_FT_MALLOC_LIB_H

#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

#define MMAP(ptr, size) mmap((ptr), (size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)

typedef struct s_pre_alloc
{

}               t_pre_alloc;

typedef struct s_zone
{
    int is_available;
    struct s_zone *next;
    void    *data;
    void    *address;
}               t_zone;

#endif //MALLOC_FT_MALLOC_LIB_H