//
// Created by aloha on 18.04.19.
//
#include "ft_malloc_lib.h"

int main()
{
    char *str;
    char *str1;
    char *str2;
    char *str3;
    char *str4;

//    str = (char*)malloc(6);
//    str1 = (char*)malloc(6);
//    int i = 0;
//    while(i < 7)
//    {
//        str[i] = 'a';
//        str1[i] = 'b';
//        i++;
//    }

//    ft_putendl(str);
//    ft_putendl(str1);
//    free(str);
    str = malloc(sizeof(char)* 1000);
    str1 = malloc(sizeof(char)* 1000);
    str2 = malloc(sizeof(char)* 1000);
    str3 = malloc(sizeof(char)* 1000);
    str4 = malloc(sizeof(char)* 100);

    return (0);
}
