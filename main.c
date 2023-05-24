#include "shell.h"

/* Extern Enveriment Variable */
/* extern char **environ; */

int main(int ac, char **env)
{

	if (ac == 1)
	{
		prompt(env);
	}

	return (0);
}
