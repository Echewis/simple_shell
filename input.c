#include "wem_karl.h"

void recieve_command(char *buffer, size_t buffer_size)
{
	ssize_t nread;
	size_t len = 0;
	char *line = NULL;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	strncpy(buffer, line, buffer_size);

	free(line);
}
