#include "wem_karl.h"

/**
 * exit_shell - This is exit function that terminates the programm
 * @inst: This is the pointer that stores the command exit
 */
void exit_shell(char *inst)
{

/*	inst[strcspn(inst, "\n")] == '\0';*/

		if (strcmp(inst, "exit") == 0)
		{
			printit("Exiting...\n");
			exit(EXIT_SUCCESS);
		}
}
