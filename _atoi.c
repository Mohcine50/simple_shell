#include "shell.h"
/**
 * _atoi - convert a string of characters to an integer value
 * @c: a string to convert
 * Return: value on success or NULL on failure
 */

int _atoi(char *c)
{
    unsigned int count = 0, size = 0, number = 0;
    unsigned int i, sign = 1, multiple = 10;

    while (*(c + count) != '\0')
    {
        if (size > 0 && (*(c + count) < '0' || *(c + count) > '9'))
            break;

        if (*(c + count) == '-')
            sign *= -1;

        if (*(c + count) >= '0' && *(c + count) <= '9')
        {
            if (size > 0)
                multiple *= 10;

            size++;
        }
        count++;
    }

    for (i = count - size; i < count; i++)
    {
        multiple /= 10;
        number = number + ((*(c + i) - '0') * multiple);
    }
    return (number * sign);
}