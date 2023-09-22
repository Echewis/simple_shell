#include "wem_karl.h"

/**
 * isInteractive - This will returns true if shell is interactive mode
 * @info: This is the structure address
 * Return: will return if interactive mode 1, 0
 */
int isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - This will checks if character is a delimeter
 * @ch: This is the character that will be checked
 * @dm: IT's the delimeter string
 * Return:It will return 1 if true and 0 if false
 */
int isDelimiter(char ch, char *dm)
{
	while (*dm)
		if (*dm++ == ch)
			return (1);
	return (0);
}

/**
 * isAlpha - This will check for alphabetic character
 * @ch: This is the character to input
 * Return: It will return 1 if c is alphabetic or 0 if otherwise
 */

int isAlpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * StringToInteger - This will convert a string to an integer
 * @st:This is the string to be converted
 * Return: It will return 0 if no numbers in string and converted number
 */

int StringToInteger(char *st)
{
	int a, sn = 1, fg = 0, outp;
	unsigned int result = 0;

	for (a = 0; st[a] != '\0' && fg != 2; a++)
	{
		if (st[a] == '-')
			sn *= -1;

		if (st[a] >= '0' && st[a] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (st[a] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sn == -1)
		outp = -result;
	else
		outp = result;

	return (outp);
}
