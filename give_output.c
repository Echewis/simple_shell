#include "wem_karl.h"

/**
 * run_command - will run the command
 * @instruct: Is a pointer to the command that  will be executed
 */
void run_command(char *instruct)
{
	int status;
	pid_t proccess_id = fork(); /* create a child process*/

	if (proccess_id == -1) /* if the child process creation failed */
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (proccess_id == 0) /* if the child process was created successfully*/
	{
		/* Execute the command specified by instruct */
		execlp(instruct, instruct, (char *)NULL);
		perror("");
		exit(EXIT_FAILURE);
	}
	else /* Tell the parent process to wait for the child process to finish */
	{
		wait(&status);
	}

}
