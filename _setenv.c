#include "shell.h"

/**
 * _setenv - function that changes or adds an environment variable
 * @name: name of the variable.
 * @value: value of the variable
 * @overwrite: takes 0 or nonzero, if zero then the value of name is not changed
 * Return: 0 on success and -1 on fail
 */

int _setenv(const char *name, const char *value, int overwrite)
{

    char *var;
    char *var_by_env;
    int name_length = strlen(name);
    int value_length = strlen(value);
    int n;

    if (name == NULL || value == NULL)
        return (-1);

    var = malloc(name_length + value_length + 2);
    if (var == NULL)
        return (-1);

    var_by_env = getenv(name);
    if (var_by_env != NULL && overwrite == 0)
    {
        free(var);
        return (0);
    }
    var = strcpy(var, name);
    var = strcat(var, "=");
    var = strcat(var, value);
    n = putenv(var);

    if (n != 0)
    {
        free(var);
        return (-1);
    }

    return (0);
}