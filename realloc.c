#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

void    *ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
    void    *result;

    if (newsize == 0)
        return (free(ptr), NULL);
    if (oldsize == 0)
    {
        result = malloc(newsize);
        if (!result)
            return (NULL);
        return (result);
    }
    result = malloc(newsize);
    if (!result)
        return (NULL);
    if (oldsize < newsize)
        ft_memcpy(result, ptr, oldsize);
    else
        ft_memcpy(result, ptr, newsize);
    free(ptr);
    return (result);
}

int main(void)
{
    char *ptr;

    ptr = (char *)malloc(sizeof(char) * 10);
    if (!ptr)
        return (1);
    int i = 0;
    while (i < 9)
    {
        ptr[i] = i + 97;
        i++;
    }
    ptr[i] = 0;
    i = 0;
    while (i < 10)
        printf("%d ", ptr[i++]);
    printf("\n");
    ft_realloc(ptr, sizeof(ptr) / sizeof(*ptr), 11);
    i = 0;
    while (i < 10)
        printf("%d ", ptr[i++]);
    printf("\n");
    return (0);
}