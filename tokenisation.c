#include "wem_karl.h"

/**
 * split_string - splits a string and print each word
 * @string: string to split
 * Return: Nothing
*/
char **split_string(char *string)
{
	char *token = NULL;
	char **args;
	int i = 0;

	args = malloc(sizeof(char *) * 150);
	token = strtok(string, " ");

	while (token != NULL)
	{
		/* printf("%s \n", token); */

		args[i] = malloc(sizeof(token) + 1);
		strcpy(args[i], token);
		token = strtok(NULL, " ");

		i++;
	}

	args[i] = NULL;

	return (args);
}
