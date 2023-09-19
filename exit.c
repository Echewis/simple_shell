#include "wem_karl.h"

/**
 * exit_shell - This is exit function that terminates the programm
 * @inst: This is the pointer that stores the command exit
 */
void exit_shell(char *inst)
{

/*	inst[strcspn(inst, "\n")] == '\0';*/

		int status;

		if (strncmp(inst, "exit", 4) == 0)
		{
			status = atoi(inst + 5);
			printf("%d\n", status);
			exit(status);
		}
}
