#include "wem_karl.h"

/**
 * main - is the main fuction
 * Return: will return positve
 */
int main(void)
{
	char instruct[125];

	while (true)
	{
		show_prompt();
		recieve_command(instruct, sizeof(instruct));
		run_command(instruct);
		exit_shell();
	}

	return (0);
}
