#include "wem_karl.h"

/**
 * run_command - will run the command
 * @instruct: Is a pointer to the command that  will be executed
 */
void run_command(char *instruct)
{
	pid_t proccess_id = fork();

	if (proccess_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (proccess_id == 0)
	{
		execlp(instruct, instruct,(char *)NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

}
