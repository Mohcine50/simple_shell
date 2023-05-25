#include "shell.h"

int main()
{

	char *input = NULL;
	size_t n = 0;
	int status, exit_code;
	ssize_t get_line;
	char **tokens;
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
			free(tokens);
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
			free(tokens);
			exit(0);
		}
		if (strcmp(input, "\n") == 0)
		{
			free(command);
			free(input);
			free(tokens);
			write(STDERR_FILENO, "\n", 1);
		}

		tokens = split_string(input, " \t\n");
		command = handle_command(tokens[0]);
		if (command == NULL)
		{
			free(command);
			free(input);
			free(tokens);
			perror("error");
		}

		fork_pid = fork();

		if (fork_pid == 0)
		{
			exit_code = execve(command, tokens, environ);
			free(command);
			free(input);
			free(tokens);
			_exit(exit_code);
		}
		else
		{
			wait(&status);
		}

		command = NULL;
		tokens = NULL;
	}

	return (0);
}
