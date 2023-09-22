#include "wem_karl.h"

/**
 * **splitStringByDelim - This will splits a string into words with a delimiter
 * @stt: This is the input string
 * @dt: This is the delimeter string
 * Return: This will return a pointer
 * to an array of strings, or NULL on failure
 */

char **splitStringByDelim(char *stt, char *dt)
{
	int a, b, y, z, nwords = 0;
	char **st;

	if (stt == NULL || stt[0] == 0)
		return (NULL);
	if (!dt)
		dt = " ";

	for (a = 0; stt[a] != '\0'; a++)
		if (!isDelimiter(stt[a], dt) && (isDelimiter(stt[a + 1], dt)
				|| !stt[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (isDelimiter(stt[a], dt))
			a++;
		y = 0;
		while (!isDelimiter(stt[a + y], dt) && stt[a + y])
			y++;

		st[b] = malloc((y + 1) * sizeof(char));
		if (!st[b])
		{
			for (y = 0; y < b; y++)
				free(st[y]);
			free(st);
			return (NULL);
		}
		for (z = 0; z < y; z++)
		st[b][z] = stt[a++];
		st[b][z] = 0;
	}
	st[b] = NULL;
	return (st);
}

/**
 * splitStringByChar - splits a string into words
 * by using a char as a delimiter
 * @stt: This is the input string
 * @dt: This is the delimeter
 * Return: It will return a pointer to an array of strings, or NULL on failure
 */
char **splitStringByChar(char *stt, char dt)
{
	int a, b, y, z, nwords = 0;
	char **st;

	if (stt == NULL || stt[0] == 0)
		return (NULL);

	for (a = 0; stt[a] != '\0'; a++)
	if ((stt[a] != dt && stt[a + 1] == dt) ||
		(stt[a] != dt && !stt[a + 1]) || stt[a + 1] == dt)
	nwords++;
	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (stt[a] == dt && stt[a] != dt)
			a++;
		y = 0;
		while (stt[a + y] != dt && stt[a + y] && stt[a + y] != dt)
			y++;
		st[b] = malloc((y + 1) * sizeof(char));
		if (!st[b])
		{
			for (y = 0; y < b; y++)
				free(st[y]);
			free(st);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			st[b][z] = stt[a++];
		st[b][z] = 0;
	}
	st[b] = NULL;
	return (st);
}
