#ifndef SHELL_H_
#define SHELL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char **split_string(char *str, const char *delim);
char *_getenv(const char *name);
int containsOnlySpaces(const char *str);
char *handle_command(char *com);
void print_shell(char *text, int length);
void shell_exit(char *command, char *input, char **tokens);
void _execve(char **argv, char *command);
int _atoi(char *c);
#endif