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

/**
 * function that builds a linked list of the PATH directories.
 */
envList_t *path_dir()
{
    char *var;
    char **PATH;
    int j = 1;
    envList_t *head;

    head = malloc(sizeof(envList_t));
    if (!head)
        return (NULL);

    var = _getenv("PATH");
    PATH = split_string(var, ":");

    head->value = strdup(PATH[0]);
    head->next = NULL;

    while (PATH[j] != NULL)
    {
        add_node_end(&head, PATH[j]);
        j++;
    }
    return (head);
}

envList_t *add_node_end(envList_t **head, const char *str)
{
    envList_t *new_node, *temp;

    if (head == NULL || str == NULL)
        return (NULL);
    new_node = malloc(sizeof(envList_t));
    if (!new_node)
        return (NULL);
    new_node->value = strdup(str);
    if (!new_node->value)
    {
        free(new_node);
        return (NULL);
    }

    if (!*head)
        *head = new_node;
    else
    {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
    free(new_node);
    return (new_node);
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
