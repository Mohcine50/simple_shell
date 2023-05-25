#include "shell.h"

/* ? advanced: Write the function without strtok */
char **split_string(char *str, const char *delim)
{
    char **words;
    char *token;
    int i = 0;

    token = strtok(str, delim);
    words = malloc(sizeof(char *) * 1024);
    while (token != NULL)
    {
        words[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    words[i] = NULL;
    return (words);
}

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

int containsOnlySpaces(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i++] != ' ')
        {
            return (-1);
        }
    }
    return (0);
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

void shell_exit(char *command, char *input, char **tokens)
{
    int num_exit = 0;

    if (tokens[1])
        num_exit = _atoi(tokens[1]);

    free(command);
    free(input);
    free(tokens);
    exit(num_exit);
}

void _execve(char **argv, char *command)
{

    if (command)
        execve(command, argv, environ);
    else
        perror("error");

    free(argv);
    exit(0);
}