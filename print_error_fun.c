#include "shell.h"
/**
 * err_num - converts a string to an integer
 * @s: the string to be converted
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
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
void print_error(info_s *info, char *estr)
{
	puts_err(info->prog_name);
	puts_err(": ");
	print_dec(info->lines, STDERR_FILENO);
	puts_err(": ");
	puts_err(info->argv[0]);
	puts_err(": ");
	puts_err(estr);
}

/**
 * puts_err - prints an input string
 * @str: the string to be printed
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
 * putchar_err - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int putchar_err(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * write_char - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int write_char(char c, int fd)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
