#include "wem_karl.h"

/**
 * recieve_command - will receive command form the usser
 * @buffer: Is the character pointer
 * @buffer_size: is the size of the string
 */
void recieve_command(char *buffer, size_t buffer_size)
{
	if (fgets(buffer, buffer_size, stdin) == NULL)
	{

		if (feof(stdin))
		{
			printit("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printit("Error...\n");
			exit(EXIT_FAILURE);
		}
	}
/*	buffer[strcspn(buffer, "\n")] == '\0';*/
}
