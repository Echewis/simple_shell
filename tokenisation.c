#include "wem_karl.h"

/**
 * split_string - splits a string and print each word
 * @string: string to split
 * @delimiter: delimiter
 * Return: Nothing
*/
void split_string(char *string, const char *delimiter)
{
	char *token;

	token = strtok(string, delimiter);

	while (token != NULL)
	{
		printf("%s \n", token);
		token = strtok(NULL, delimiter);
	}

}
