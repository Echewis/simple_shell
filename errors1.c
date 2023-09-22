#include "wem_karl.h"

/**
 * ErrorStringToInteger - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, cnumber otherwise
 * -1 if error
 */
int ErrorStringToInteger(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * printErrorMessage - prints an error message
 * @info: information about the shell's state
 * @error_str: string specified the error
 *
 * Return: Nothing
 */
void printErrorMessage(info_t *info, char *error_str)
{
	printInputString(info->fname);
	printInputString(": ");
	printDecimalNumber(info->line_count, STDERR_FILENO);
	printInputString(": ");
	printInputString(info->argv[0]);
	printInputString(": ");
	printInputString(error_str);
}

/**
 * printDecimalNumber - function prints a decimal number
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimalNumber(int input, int fd)
{
	int (*__putchar)(char) = putChar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = printChar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * NumberToString - convert a number to string
 * @num: number
 * @base: base of the number
 * @flags: argument flags
 *
 * Return: string
 */
char *NumberToString(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void removeComments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}
