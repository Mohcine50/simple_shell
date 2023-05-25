#include "shell.h"

void prompt(char **env)
{
    char *input = NULL;
    size_t n = 0;
    int status, i = 0, exit_code;
    ssize_t get_line;
    char **token;
    pid_t fork_pid;
    char *command;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDIN_FILENO, "csisfun$ ", 9);

        get_line = getline(&input, &n, stdin);

        if (get_line == -1)
        {
            free(command);
            free(input);
            free(token);
            exit(0);
        }
        if (get_line == 0)
        {
            if (isatty(STDIN_FILENO))
                write(STDERR_FILENO, "\n", 1);
            exit(0);
        }

        if (strcmp(input, "exit\n") == 0)
        {
            free(command);
            free(input);
            free(token);
            exit(0);
        }
        if (strcmp(input, "\n") == 0)
        {
            free(command);
            free(input);
            free(token);
            write(STDERR_FILENO, "\n", 1);
        }

        /*   while (input[i])
          {
              if (input[i] == '\n')
              {
                  input[i] = '\0';
              }
              i++;
          } */

        token = split_string(input, " \t\n");
        command = handle_command(token[0]);
        if (command == NULL)
        {
            free(command);
            free(input);
            free(token);
            perror("error");
        }

        fork_pid = fork();

        if (fork_pid == 0)
        {
            exit_code = execve(command, token, env);
            free(command);
            free(input);
            free(token);
            _exit(exit_code);
        }
        else
        {
            wait(&status);
        }

        command = NULL;
        token = NULL;
    }
}