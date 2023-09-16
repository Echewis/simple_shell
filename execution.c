#include "wem_karl.h"

/**
 * exe_file - execute a command
 * @instruct: command to execute
*/
void exe_file(char *instruct)
{
	char *path;
	char **args;

	args = split_string(instruct);

	if (args)
	{
		path = "/bin/";
		if (execve(path, args, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
}
