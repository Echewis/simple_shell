#include "wem_karl.h"

/**
 * *getHistoryFileName - This will get the history file
 * @info:  This is the parameter structure
 * Return: allocated string containg history file
 */

char *getHistoryFileName(info_t *info)
{
	char *b, *d;

	d = getEnvironVariable(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (getStrLen(d) + getStrLen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	copyStr(b, d);
	concatStr(b, "/");
	concatStr(b, HIST_FILE);
	return (b);
}

/**
 * writeHistoryToFile - This will creates a file or append it
 * to the existing file
 * @info: This is the parameter structure
 * Return:It will return 1 on success, else -1
 */
int writeHistoryToFile(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFileName(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		writeStringToFile(node->str, fd);
		writeCharToFile('\n', fd);
	}
	writeCharToFile(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistoryFromFile - This will read the history from file
 * @info: this is the parameter structure
 * Return: It will rwturn histcount on success or 0
 */
int readHistoryFromFile(info_t *info)
{
	int a, l = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *filename = getHistoryFileName(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(fd, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(b), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (b[a] == '\n')
		{
			b[a] = 0;
			buildHistoryList(info, b + l, linecount++);
			l = a + 1;
		}
	if (l != a)
		buildHistoryList(info, b + l, linecount++);
	free(b);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - This will add entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @b: Is the buffer
 * @l: This is the line count
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *b, int l)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	insertNodeAtEnd(&node, b, l);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - This will re-numbers the history linked list
 * @info: This is the Structure containing potential arguments
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
