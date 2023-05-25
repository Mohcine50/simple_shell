#include "shell.h"

/**
 * _getenv - get the envirment variable from environ
 * @name: env varibale name
 * Return: return the pointer of the env var string on success or NULL
 */
char *_getenv(const char *name)
{
	int i = 0;
	char *splited_env;
	char *env_value;

	while (environ[i])
	{
		splited_env = strtok(environ[i], "=");
		if (strcmp(splited_env, name) == 0)
		{
			env_value = strtok(NULL, "=");
			return (env_value);
		}
		i++;
	}
	return (NULL);
}

/**
 * print_shell - check the file
 * @text: text string of what we want to print
 * @length: lenght of text
 */
void print_shell(char *text, int length)
{
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, text, length);
}

/**
 * shell_exit - handle the exit commande
 * @command: the user command
 * @input: the user input
 * @argv: the array of args
 */
void shell_exit(char *command, char *input, char **argv)
{
	int num_exit = 0;

	if (argv[1])
		num_exit = _atoi(argv[1]);

	free(command);
	free(input);
	free(argv);
	exit(num_exit);
}

/**
 * _execve - handle the execute command
 * @argv: array of args entred from the user
 */
void _execve(char **argv)
{
	char *command = handle_command(argv[0]);

	if (command)
		execve(command, argv, environ);
	else
		perror("error");

	free(argv);
	exit(0);
}
