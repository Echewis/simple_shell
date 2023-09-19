#include "wem_karl.h"

/**
 * exit_shell - This is exit function that terminates the programm
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
