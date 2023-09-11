#include "wem_karl.h"
/**
 * recieve_command - recieves inputs from the user
 * @st_c: this is the address to the inputed commands
 * @how_big: This is the size of the command
 */
void recieve_command(char *st_c, size_t how_big)
{
	if (fgets(st_c, how_big, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printit("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printit("Error, Try Again");
			exit(EXIT_SUCCESS);
		}
	}
	st_c[strcspn(st_c, "\n")] = '\0';
}
