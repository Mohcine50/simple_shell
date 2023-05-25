#ifndef SHELL_H_
#define SHELL_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

char **split_string(char *str, const char *delim);
char *_getenv(const char *name);
char *handle_command(char *com);
void print_shell(char *text, int length);
void shell_exit(char *command, char *input, char **argv);
void _execve(char **argv);
int _atoi(char *c);
#endif
