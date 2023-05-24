#include "shell.h"

void prompt(char **env)
{
    char *input = NULL;
    size_t n = 0;
    int status, i = 0, check_command;
    ssize_t get_line;
    char **token;
    pid_t fork_pid;
    char *command;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");
        get_line = getline(&input, &n, stdin);

        if (get_line == -1)
        {
            free(input);
            exit(EXIT_FAILURE);
        }

        if (strcmp(input, "exit\n") == 0)
        {
            free(input);
            exit(EXIT_SUCCESS);
        }
        if (strcmp(input, "\n") == 0)
        {
            continue;
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
            else
            {
                fork_pid = fork();

                if (fork_pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                if (fork_pid == 0)
                {

                    if (execve(command, token, env) == -1)
                    {
                        perror("Error");
                        /* exit(EXIT_FAILURE) */;
                    }
                }
                else
                {
                    wait(&status);
                }
            }
        }
    }

    free(input);
    free(token);
}