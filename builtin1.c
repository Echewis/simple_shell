#include "wem_karl.h"

/**
 * history - displays the history list, one by one
 * @info: information about the shell's state
 *
 * Return: Always 0
 */
int history(info_t *info)
{
	printListElements(info->history);
	return (0);
}

/**
 * unset_alias - unsets alias to string
 * @info: information about the shell's state
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 for fail
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = findChar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, findNodeStartingWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: information about the shell's state
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = findChar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (insertNodeAtEnd(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = findChar(node->str, '=');
		for (a = node->str; a <= p; a++)
		putChar(*a);
		putChar('\'');
		putStr(p + 1);
		putStr("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias - the alias builtin (man alias)
 * @info: information about the shell's state
 *
 * Return: Always 0
 */
int alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = findChar(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(findNodeStartingWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
