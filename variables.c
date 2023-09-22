#include "wem_karl.h"

/**
 * isChain - test if the buffer is a chain delimeter
 * @info: information about the shell's state
 * @buffer: the string buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if true, 0 otherwises
 */
int isChain(info_t *info, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* the end of the command */
	{
		buffer[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;

	return (1);
}

/**
 * checkChain - checks for a chains
 * @info: information about the shell's state
 * @buffer: the char buffer
 * @pos: address of current position in buf
 * @start: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buffer, size_t *pos
		, size_t start, size_t len)
{
	size_t a = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			a = len;
		}
	}

	*pos = a;
}

/**
 * replaceAliases - replaces an aliases in the tokenized string
 * @info: information about the shell's state
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = findNodeStartingWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = findChar(node->str, '=');
		if (!p)
			return (0);
		p = duplicateStr(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: information about the shell's state
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compareStr(info->argv[i], "$?"))
		{
			replaceStringInArray(&(info->argv[i]),
					duplicateStr(NumberToString(info->status, 10, 0)));
			continue;
		}
		if (!compareStr(info->argv[i], "$$"))
		{
			replaceStringInArray(&(info->argv[i]),
					duplicateStr(NumberToString(getpid(), 10, 0)));
			continue;
		}
		node = findNodeStartingWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceStringInArray(&(info->argv[i]),
					duplicateStr(findChar(node->str, '=') + 1));
			continue;
		}
		replaceStringInArray(&info->argv[i], duplicateStr(""));

	}
	return (0);
}

/**
 * replaceStringInArray - replaces string in an array of string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceStringInArray(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
