#include "shell.h"

/* Extern Enveriment Variable */
/* extern char **environ; */

int main(int ac, char **av, char **env)
{

	if (ac == 1)
	{
		prompt(av[0], env);
	}

	return (0);
}
