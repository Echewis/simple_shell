#include "wem_karl.h"

/**
 * main - is the main fuction
 * Return: will return positve
 */
int main(void)
{
	char instruct[1024];

	while (true)
	{
		show_prompt();
		recieve_command(instruct, sizeof(instruct));
		exit_shell(instruct);
		env(instruct);
		run_command(instruct);
	}
	return (0);
}
