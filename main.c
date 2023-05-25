#include "shell.h"

/**
 * main - shell excute point
 * Return: 0 on success or 1 otherwise
 */
int main(void)
{
	char *input = NULL, *command = NULL;
	char **argv = NULL;
	size_t input_size = 0;
	pid_t fork_pid;
	int status, _getline;

	while (1)
	{
		print_shell("alc@shell$ ", 11);
		_getline = getline(&input, &input_size, stdin);
		if (_getline == -1)
		{
			free(command);
			free(input);
			free(argv);
			exit(0);
		}
		if (_getline == 0)
			print_shell("\n", 1), exit(1);

		argv = split_string(input, " \t\n");
		if (argv[0] && strcmp(argv[0], "exit") == 0)
			shell_exit(command, input, argv);

		fork_pid = fork();
		if (fork_pid == -1)
		{
			perror("error");
			return (1);
		}
		if (fork_pid == 0)
			_execve(argv);
		else
			wait(&status);
		free(command);
		free(argv);
		command = NULL;
		argv = NULL;
	}
	return (0);
}
