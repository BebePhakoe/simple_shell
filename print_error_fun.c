#include "btshell.h"
/**
 * err_num - Converts string to integer
 * @s: String to convert
 * Return: 0 if no numbers in string,
 * converted integer else -1
 *
 */
int err_num(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * print_error - Prints an error message
 * @array: Parameter struct
 * @estr: String containing specified error types
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
void print_error(info_q *array, char *estr)
{
	puts_err(array->prog_name);
	puts_err(": ");
	print_dec(array->lines, STDERR_FILENO);
	puts_err(": ");
	puts_err(array->argv[0]);
	puts_err(": ");
	puts_err(estr);
}

/**
 * puts_err - Prints an input string
 * @str: String to  print
 *
 * Return: Nothing
 */
void puts_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_err(str[i]);
		i++;
	}
}
/**
 * putchar_err - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int putchar_err(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEGATIVE_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEGATIVE_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * write_char - Writes the character c to given bt
 * @c: The character to print
 * @bt: Filedescriptor
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int write_char(char c, int bt)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEGATIVE_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(bt, buf, i);
		i = 0;
	}
	if (c != NEGATIVE_ONE)
		buf[i++] = c;
	return (1);
}
