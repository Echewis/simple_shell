#include "wem_karl.h"

/**
 * env - prints the current environment
 * @instruct: command
*/
void env(const char *instruct)
{
	int i;

	if (strcmp(instruct, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printit(environ[i]);
			printit("\n");
		}
	}
}
