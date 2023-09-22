#include "wem_karl.h"

/**
 * **getEnvList - This will return the string array copy of our environment
 * @info: This is the struct containing potential argument
 * Return: It will return  0
 */
char **getEnvList(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convertListToStringArray(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnvVariable - This will remove an environment variable
 * @v: this the variable
 * @info: This is the Struct containing potential arguments
 * Return: This will return 1 on delete and 0 otherwise
 */
int unsetEnvVariable(info_t *info, char *v)
{
	list_t *node = info->env;
	size_t a = 0;
	char *pt;

	if (!node || !v)
		return (0);

	while (node)
	{
		pt = starts_with(node->str, v);
		if (pt && *pt == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * setEnvVariable - This will initialize a new environment variable,
 * @info: Structure containing potential arguments
 * @v: This is thee string env var property
 * @val: This is the string env var value
 *  Return:This will Return  0
 */
int setEnvVariable(info_t *info, char *v, char *val)
{
	char *b = NULL;
	list_t *node;
	char *pt;

	if (!v || !val)
		return (0);

	b = malloc(getStrLen(v) + getStrLen(val) + 2);
	if (!b)
		return (1);
	copyStr(b, v);
	concatStr(b, "=");
	concatStr(b, val);
	node = info->env;
	while (node)
	{
		pt = starts_with(node->str, v);
		if (pt && *pt == '=')
		{
			free(node->str);
			node->str = b;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	insertNodeAtEnd(&(info->env), b, 0);
	free(b);
	info->env_changed = 1;
	return (0);
}
