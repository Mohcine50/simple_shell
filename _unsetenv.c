#include "shell.h"

/**
 * function that deletes the variable name from the environment
 */

int _unsetenv(const char *name)
{
    char *var;
    int n;
    char *env_var;

    env_var = getenv(name);
    if (env_var == NULL)
        return (-1);

    var = malloc(strlen(name) + 1);
    if (var == NULL)
        return (-1);
    var = strcpy(var, name);
    var = strcat(var, "=");

    n = putenv(var);
    if (n != 0)
    {
        free(var);
        return (-1);
    }
    return (0);
}
