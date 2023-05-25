#include "shell.h"

int main()
{

	char *input = NULL, **tokens = NULL, *command = NULL;
	int status;
	ssize_t get_line;
	size_t n = 0;
	pid_t fork_pid;

	while (1)
	{
		print_shell("alx:shell$ ", 11);

		get_line = getline(&input, &n, stdin);

		if (get_line == -1)
		{

			free(input);
			exit(0);
		}
		if (get_line == 0)
		{
			print_shell("\n", 1);
			exit(1);
		}
		tokens = split_string(input, " \t\n");
		command = handle_command(tokens[0]);
		if (tokens[0] && strcmp(input, "exit") == 0)
		{
			shell_exit(command, input, tokens);
		}
		/* if (strcmp(input, "\n") == 0)
		{
			free(command);
			free(input);
			free(tokens);
			write(STDERR_FILENO, "\n", 1);
		} */

		fork_pid = fork();

		if (fork_pid == -1)
		{
			perror("error");
			return (1);
		}
		if (fork_pid == 0)
		{
			_execve(tokens, command);
		}
		else
		{
			wait(&status);
		}

		free(command);
		free(tokens);
		command = NULL;
		tokens = NULL;
	}

	return (0);
}
