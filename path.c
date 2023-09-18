#include "wem_karl.h"
/**
 * get_path - give the full path to the given command
 * @command: command typing by the user
 *
 * Return: the path or NULL if the path is not executable
 */
char *get_path(char *command)
{
	char cmd_path[150];
	char *path = our_getenv("PATH");
	char *directory = strtok(path, ":");

	while (directory != NULL)
	{
		snprintf(cmd_path, sizeof(cmd_path), "%s/%s", directory, command);
		if (access(cmd_path, X_OK) == 0)
		{
			return (our_strdup(cmd_path));
		}
		directory = strtok(NULL, ":");
	}

	return (NULL);
}
