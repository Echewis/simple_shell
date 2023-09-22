#include "wem_karl.h"

/**
 * getStrLen - This will returns length of a string
 * @s: the string whose length to check
 * Return: integer length of string
 */
int getStrLen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * compareStr - This will performs lexicogarphic comparison of two strangs.
 * @s1: This is the first String
 * @s2: Also the second one
 * Return: It will return negative if s1 < s2
 */
int compareStr(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * *starts_with - checks if needle starts with haystack
 * @h: string to search
 * @n: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}

/**
 * *concatStr - This will concatenates two strings
 * @d: is the destination pointer
 * @s: this is the source pointer
 *
 * Return: will return the pointer to destination pointer
 */
char *concatStr(char *d, char *s)
{
	char *r = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (r);
}
