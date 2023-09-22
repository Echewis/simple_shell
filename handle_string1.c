#include "wem_karl.h"
/**
 * *copyStr - This will copies a string
 * @d: This is the destination
 * @s: this is the source
 * Return:This will return a pointer to the destination
 */
char *copyStr(char *d, char *s)
{
	int a = 0;

	if (d == s || s == 0)
		return (d);
	while (s[a])
	{
		d[a] = s[a];
		a++;
	}
	d[a] = 0;
	return (d);
}

/**
 * *duplicateStr - This will duplicates  string
 * @s: this is the string to be duplicated
 * Return: This will return pointer to the duplicated string
 */
char *duplicateStr(const char *s)
{
	int length = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;
	r = malloc(sizeof(char) * (length + 1));
	if (!r)
		return (NULL);
	for (length++; length--;)
		r[length] = *--s;
	return (r);
}

/**
 * putStr - This will prints an input string
 * @s: this is the string to be printed
 * Return:It will return Nothing
 */
void putStr(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		putChar(s[a]);
		a++;
	}
}

/**
 * putChar -This will  writes the character ch to stdout_fileno
 * @ch: The character to print
 * Return: It will return success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putChar(char ch)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buf[a++] = ch;
	return (1);
}
