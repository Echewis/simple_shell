#include "wem_karl.h"

/**
 * run_command - will run the command
 * @instruct: Is a pointer to the command that  will be executed
 */
void run_command(char *instruct)
{
	char *argz[] = {instruct, NULL};
	pid_t proccess_id = fork();

	if (proccess_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (proccess_id == 0)
	{
		execve(instruct, argz, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

}
