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
		run_command(instruct);
		recieve_command(instruct, sizeof(instruct));
	}
	return (0);
}
