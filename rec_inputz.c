#include "wem_karl.h"
/**
 * recieve_command - recieves inputs from the user
 * @buffer: buffer that will store command
 * @buffer_size: This is the size of the buffer
 */
void recieve_command(char *buffer, size_t buffer_size)
{
	/*ssize_t read;*/
	size_t len = 0;

	if (getline(&buffer, &buffer_size, stdin) == -1)
	{
		printit("Error.... Try again\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		len = strlen(buffer);

		if (len > 0 && buffer[len - 1] == '\n')
		{
			buffer[len - 1] = '\0';
		}
	}

}
