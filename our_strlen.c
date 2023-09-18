#include "wem_karl.h"

/**
 * our_strlen - len of a string
 * @s: parameter
 *
 * Return: the len of *s
 *
 */

int our_strlen(char *s)
{
	int i = 0;

	while (*(s + i))
		i++;

	return (i);
}
