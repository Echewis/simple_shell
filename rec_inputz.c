#include "wem_karl.h"
/**
 * recieve_command - recieves inputs from the user
 * @buffer: buffer that will store command
 * @buffer_size: This is the size of the buffer
 */
void recieve_command(char *buffer, size_t buffer_size)
{
	/* reads at most buffer_size -1 and store it in buffer*/
	while (fgets(buffer, buffer_size, stdin) == NULL)
	{
		if (feof(stdin)) /* if the end of input has been reached */
		{
			printit("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printit("Error, Try Again\n");
			exit(EXIT_SUCCESS);
		}

	}
	buffer[strcspn(buffer, "\n")] = '\0'; /* terminate additionnal line */
}
