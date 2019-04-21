//
// Created by aloha on 18.04.19.
//
#include "inc/ft_malloc_lib.h"

int main()
{
    char *str;
    char *str1;
    char *str2;
    char *str3;

    str = malloc(sizeof(char)* 1000);
    str1 = malloc(sizeof(char)* 1000);
    str2 = malloc(sizeof(char)* 1000);
    str3 = malloc(sizeof(char)* 5000);
    str2 = realloc(str2, 2000);

    free(str3);
    show_alloc_mem();

    return (0);
}
