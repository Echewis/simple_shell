#include "wem_karl.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: athe size of buffer
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSIGINT);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = getLine(info, buffer, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * readInput - gets a line minus the newline
 * @info: information about the shell's state
 *
 * Return: bytes read
 */
ssize_t readInput(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	putChar(BUF_FLUSH);
	bytes_read = input_buf(info, &buffer, &len);
	if (bytes_read == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		checkChain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (getStrLen(p));
	}

	*buf_p = buffer;
	return (bytes_read);
}

/**
 * read_buf - reads a buffer
 * @info: information about the shell's state
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t readed = 0;

	if (*i)
		return (0);
	readed = read(info->readfd, buf, READ_BUF_SIZE);
	if (readed >= 0)
		*i = readed;
	return (readed);
}

/**
 * getLine - gets the next line of input from STDIN
 * @info: information about the shell's state
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int getLine(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = findChar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocMemory(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concatNChar(new_p, buf + i, k - i);
	else
		copyNChar(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handleSIGINT - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handleSIGINT(__attribute__((unused))int sig_num)
{
	putStr("\n");
	putStr("wem_karl_$ ");
	putChar(BUF_FLUSH);
}
