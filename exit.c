#include "wem_karl.h"

/**
 * exit_shell - This is exit function that terminates the programm
 */
void exit_shell(void)
{
	char inst[150];
	while (1)
	{
	fgets(inst, sizeof(inst), stdin);
	inst[strcspn(inst, "\n")] == '\0';

		if (strcmp(inst, "exit") == 0)
		{
			printit("Exiting...");
			exit(EXIT_SUCCESS);
		}
	}
}
/*

void exit_s(const char *s)
{
	if (strcmp(s, "exit") == 0)
	{
		exit(0);
	}
}*/
