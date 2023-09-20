#include "wem_karl.h"
/**
 * recieve_command - recieves inputs from the user
 * @buffer: buffer that will store command
 * @buffer_size: This is the size of the buffer
 */
void recieve_command(char *buffer, size_t buffer_size)
{
	ssize_t read;
	size_t len = 0;

		if ((read = getline(&buffer, &buffer_size, stdin)) != -1)
	{
		len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n')
		{
			buffer[len - 1] = '\0';
		}
	}
	
	else
	{
		printit("Error, Try Again\n");
		exit(EXIT_FAILURE);
	}
	
}
