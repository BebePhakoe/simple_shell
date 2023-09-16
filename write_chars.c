#include "main.h"

/**
 * write_chars - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_chars(char *str, int bt)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char(*str++, fd);
	}
	return (i);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = putchar_err;
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
 * change_base - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *change_base(long int num, int base, int flags)
{
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	static char *array;
	static char buffer[50];

	if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * handle_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: 0;
 */

void handle_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
