#include "wem_karl.h"

/**
 * clearInfo - This will initializes info_t struct
 * @info:This is the structure address
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - This will initializes info_t structure
 * @info: This is the structure address
 * @av: This is the argument vector
 */
void setInfo(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitStringByDelim(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateStr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replaceAliases(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - This will frees info_t structure fields
 * @info: This is the structure address
 * @a: It will be true if Its freeing all fields
 */
void freeInfo(info_t *info, int a)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (a)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLinkedList(&(info->env));
		if (info->history)
			freeLinkedList(&(info->history));
		if (info->alias)
			freeLinkedList(&(info->alias));
		freeStringArray(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		putChar(BUF_FLUSH);
	}
}
