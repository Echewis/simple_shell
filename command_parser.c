#include "wem_karl.h"

/**
 * isCommandInPath - determines if a command is in the path
 * @info: information about the shell's state
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCommandInPath(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copySubstring - copy a part of a string
 * @pathstr: the path string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *copySubstring(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * findExecutablePath - find if the command is in the pathstr
 * @info: information about the shell's state
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of command if found or NULL otherwise
 */
char *findExecutablePath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((getStrLen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (isCommandInPath(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = copySubstring(pathstr, curr_pos, i);
			if (!*path)
				concatStr(path, cmd);
			else
			{
				concatStr(path, "/");
				concatStr(path, cmd);
			}
			if (isCommandInPath(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
