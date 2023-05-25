#include "shell.h"
/**
 * _atoi - convert a string of characters to an integer value
 * @c: a string to convert
 * Return: value on success or NULL on failure
 */

int _atoi(char *c)
{
	unsigned int count = 0, size = 0, number = 0;
	unsigned int i, sign = 1, multiple = 10;

	while (*(c + count) != '\0')
	{
		if (size > 0 && (*(c + count) < '0' || *(c + count) > '9'))
			break;

		if (*(c + count) == '-')
			sign *= -1;

		if (*(c + count) >= '0' && *(c + count) <= '9')
		{
			if (size > 0)
				multiple *= 10;

			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		multiple /= 10;
		number = number + ((*(c + i) - '0') * multiple);
	}
	return (number * sign);
}

/**
 * split_string - split a given string by the delim
 * @str: the string that we want to split
 * @delim: the delimeter to split with
 * Return: a pointer to splited buffer or NULL
 */
char **split_string(char *str, const char *delim)
{
	char **words;
	char *token;
	int i = 0;

	token = strtok(str, delim);
	words = malloc(sizeof(char *) * 1024);
	while (token != NULL)
	{
		words[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	words[i] = NULL;
	return (words);
}


/**
 * handle_command - check if the command on dir
 * if not generate a command dir and check it
 * @com: command provided by the user
 * Return: pointer of the dir or NULL
 */
char *handle_command(char *com)
{
	char *PATH;
	char *command;
	char *token;
	struct stat _stat;

	PATH = _getenv("PATH");
	token = strtok(PATH, ":");

	if (stat(com, &_stat) == 0)
		return (com);
	while (token)
	{
		command = malloc(strlen(token) + strlen(com) + 2);

		strcpy(command, token);
		strcat(command, "/");
		strcat(command, com);
		if (stat(command, &_stat) == 0)
			return (command);

		free(command);
		token = strtok(NULL, ":");
	}

	return (NULL);
}


