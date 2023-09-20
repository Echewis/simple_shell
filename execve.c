#include "wem_karl.h"

/**
 * execute_c - will execute the command
 * @inst: is the pointer to the string
 */
void execute_c(char *inst)
{
	char *args[70];
	char *token;
	int a = 0;
	pid_t pid = fork();

	token = strtok(inst, " ");
	while (token != NULL)
	{
		args[a++] = token;
		token = strtok(NULL, " ");
	}
	args[a] = NULL;

	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		printit("Error...\n");
		exit(EXIT_FAILURE);
	}
}
