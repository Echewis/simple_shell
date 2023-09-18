#include "wem_karl.h"

/**
 * our_strncmp - unction to compare the first n characters of str1 and str2
 * @str1: first string
 * @str2: second string
 * @n: number of byte
 *
 * Return: 0 for success
*/
int our_strncmp(char *str1, char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}

		if (*str1 == '\0')
			break;
		str1++;
		str2++;
		n--;
	}

	return (0);
}
