#include "wem_karl.h"

/**
 * copyNChar - copies n character in a string
 * @dest: the destination string
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the concatenated string
 */
char *copyNChar(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * concatNChar - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @n: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *concatNChar(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * findChar - find a character in a string
 * @s: the string where we find character
 * @c: the character to be find
 *
 * Return: a pointer to the string
 */
char *findChar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
