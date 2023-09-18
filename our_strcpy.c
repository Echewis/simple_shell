#include "wem_karl.h"

/**
 * our_strcpy - copy in string into another.
 * @dest: destination string
 * @src: source string
 *
 * Return: Nothing
 */
void *our_strcpy(char *dest, const char *src)
{
	char *original = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
}
