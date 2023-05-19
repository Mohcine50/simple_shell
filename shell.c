#include "shell.h"

/* ? advanced: Write the function without strtok */
char **split_string(char *str, const char *delim)
{
    char **words = NULL;
    char *token = strtok(str, delim);
    int i = 0;

    while (token != NULL)
    {
        words = realloc(words, (i + 1) * sizeof(char *));
        words[i] = strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    words[i] = NULL;
    return (words);
}

/**
 * _getenv - get a
 */
extern char **environ;
char *_getenv(const char *name)
{
    char **variables = environ;
    char **variable_values;

    while (*variables != NULL)
    {
        if (strstr(*variables, name) != NULL)
        {
            variable_values = split_string(*variables, "=");
            return (variable_values[1]);
        }
        variables++;
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
