#include "shell.h"

/* Extern Enveriment Variable */
/* extern char **environ; */

int main(int ac, char **av, char **env)
{
	char *input;
	size_t n = 0;
	int status, i = 0;
	ssize_t get_line;
	char **token;
	pid_t fork_pid;

	/*
	°°°°°°°°°°°°°°For Printing PAPTH Links°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
	char *var;
	char **PATH;
	int j = 0;
	var = _getenv("PATH");
	PATH = split_string(var, ":");
	while (PATH[j] != NULL)
	{
		printf("%s\n", PATH[j++]);
	} */

	/*
	°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Used to print the environ variables usin extern variable °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
	while (environ[e] != NULL)
	{
		printf("%s\n", environ[e]);
		e++;
	}
 */

	/* °°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Add Path to linked list and print it °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
	envList_t *head = path_dir();
	print_list(head); */

	if (ac == 1)
	{
		/* Print The Args */
		while (1)
		{
			if (isatty(STDIN_FILENO))
				printf("%s$ ", av[0]);
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
			while (input[i])
			{
				if (input[i] == '\n')
				{
					input[i] = 0;
				}
				i++;
			}

			fork_pid = fork();

			if (fork_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (fork_pid == 0)
			{
				token = split_string(input, " ");
				if (execve(token[0], token, env) == -1)
				{
					perror("Error:");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait(&status);
			}
		}

		free(input);
	}

	return (0);
}