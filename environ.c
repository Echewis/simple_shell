#include "wem_karl.h"

/**
 * EnvCommand - prints the current environment
 * @info: information about the shell's state
 * Return: Always 0
 */
int EnvCommand(info_t *info)
{
	printStringList(info->env);
	return (0);
}

/**
 * getEnvironVariable - gets the value of an environ variable
 * @info: information about the shell's state
 * @name: name of the environment variable
 *
 * Return: the value
 */
char *getEnvironVariable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * SetEnvCommand - Initialize a new environment variable
 * @info: information about the shell's state
 *
 * Return: Always 0
 */
int SetEnvCommand(info_t *info)
{
	if (info->argc != 3)
	{
		printInputString("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnvVariable(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * UnsetEnvCommand - Remove an environment variable
 * @info: information about the shell's state
 *
 * Return: Always 0
 */
int UnsetEnvCommand(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		printInputString("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnvVariable(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates env linked list
 * @info: information about the shell's state
 *
 * Return: Always 0
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		insertNodeAtEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
