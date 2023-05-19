#include "shell.h"

/**
 * check if commands exist in bin
 */

int _which(char *dir)
{
    struct stat _stat;
    int result;

    result = stat(dir, &_stat);

    if (result == -1)
    {
        return (-1);
    };
    return (0);
}