#include "wem_karl.h"

/**
 * our_getenv - environment variable env_name without create it manually
 * @env_name: environment variable
 * * Return: the value of env_name if exist NULL otherwise
*/
char *our_getenv(char *env_name)
{
	if (env_name == NULL)
		return (NULL);

	for (char **env = environ; *env != NULL; env++)
	{
		char *entry = *env;

		if (our_strncmp(entry, env_name, our_strlen(env_name)) == 0)
		{
			if (entry[our_strlen(env_name)] == '=')
				/* Found a match; returns the value after the '=' character */
				return (&(entry[our_strlen(env_name) + 1]));
		}
	}

	return (NULL); /* variable not found */
}
