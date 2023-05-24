#include "shell.h"

void prompt(char **env)
{
    char *input = NULL;
    size_t n = 0;
    int status, i = 0, check_command, exit_code;
    ssize_t get_line;
    char **token;
    pid_t fork_pid;
    char *command;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDERR_FILENO, "csisfun$ ", 2);
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
            exit(1);
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

        while (input[i])
        {
            if (input[i] == '\n')
            {
                input[i] = '\0';
            }
            i++;
        }

        token = split_string(input, " \t\n");
        if (_which(token[0]) == 0)
        {
            command = token[0];
        }
        else
        {
            command = malloc(sizeof("/bin/") + sizeof(token[0]) + 2);
            sprintf(command, "%s/%s", "/bin", token[0]);
            check_command = _which(command);
            if (check_command == -1)
            {
                printf("%s: Command not found\n", token[0]);
            }
        }

        fork_pid = fork();

        if (fork_pid == -1)
        {
            free(command);
            free(input);
            free(token);
            exit(-1);
        }
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
            free(command);
            free(input);
            free(token);
            command = NULL;
            token = NULL;
        }
    }
}