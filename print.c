#include "wem_karl.h"

/**
 * printit - print a string on the terminal
 * @okwu: string to be printed
 * Return: Nothing
*/
void printit(const char *okwu)
{
	int i = 0;

	while (okwu[i] != '\0')
	{
		write(1, &okwu[i], 1);
		i++;
	}
}
