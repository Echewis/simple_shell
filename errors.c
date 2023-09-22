#include "wem_karl.h"

/**
 * printInputString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printInputString(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		printChar(str[i]);
		i++;
	}
}

/**
 * printChar - writes the character c to stderr
 * @c: The character to be printed
 *
 * Return: On success 1
 */
int printChar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * writeCharToFile - writes the character c to given fd
 * @c: The character to be printed
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1
 */
int writeCharToFile(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeStringToFile - write string into a files
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int writeStringToFile(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writeCharToFile(*str++, fd);
	}
	return (i);
}
