#include "wem_karl.h"

/**
 * printit - is the prototype that prints output
 * @okwu: this is the address of inputed commands
 */
void printit(const char *okwu)
{
	write(STDOUT_FILENO, okwu, strlen(okwu));
}
