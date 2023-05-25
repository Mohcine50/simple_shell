#ifndef SHELL_H_
#define SHELL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * description: struct for path env variables
 */

extern char **environ;
typedef struct env_s
{
    char *value;
    struct env_s *next;
} envList_t;

char **split_string(char *str, const char *delim);
char *_getenv(const char *name);
envList_t *path_dir();
size_t print_list(const envList_t *h);
envList_t *add_node_end(envList_t **head, const char *str);

int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int containsOnlySpaces(const char *str);
void print_env(char **env);
char *handle_command(char *com);
#endif