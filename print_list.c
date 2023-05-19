#include "shell.h"

/**
 * print path linked list
 */
size_t print_list(const envList_t *h)
{
    size_t i = 0;

    while (h)
    {
        if (h->value == NULL)
        {
            printf("[0] (nil)\n");
        }
        else
            printf("%s\n", h->value);
        h = h->next;
        i++;
    }
    return (i);
}