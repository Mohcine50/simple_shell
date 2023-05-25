#include "shell.h"

/**
 * _getenv - get a
 */
char *_getenv(const char *name)
{
    int i = 0;
    char *splited_env;
    char *env_value;

    while (environ[i])
    {
        splited_env = strtok(environ[i], "=");
        if (strcmp(splited_env, name) == 0)
        {
            env_value = strtok(NULL, "=");
            return (env_value);
        }
        i++;
    }
    return (NULL);
}

char *handle_command(char *com)
{
    char *PATH;
    char *command;
    char *token;
    struct stat _stat;

    PATH = _getenv("PATH");
    token = strtok(PATH, ":");

    if (stat(com, &_stat) == 0)
        return (com);
    else
        while (token)
        {
            command = malloc(strlen(token) + strlen(com) + 2);

            strcpy(command, token);
            strcat(command, "/");
            strcat(command, com);
            if (stat(command, &_stat) == 0)
                return (command);

            free(command);
            token = strtok(NULL, ":");
        }

    return (NULL);
}

void print_shell(char *text, int length)
{
    if (isatty(STDIN_FILENO))
        write(STDERR_FILENO, text, length);
}

void shell_exit(char *command, char *input, char **argv)
{
    int num_exit = 0;

    if (argv[1])
        num_exit = _atoi(argv[1]);

    free(command);
    free(input);
    free(argv);
    exit(num_exit);
}

void _execve(char **argv)
{
    char *command = handle_command(argv[0]);
    if (command)
        execve(command, argv, environ);
    else
        perror("error");

    free(argv);
    exit(0);
}