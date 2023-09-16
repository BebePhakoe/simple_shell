#include "btshell.h"

/**
 * print_dec - Function that prints a decimal
 * @input: Input
 * @bt: Filedescriptor
 *
 * Return: Number of characters printed
 */
int print_dec(int input, int bt)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, cur;

	if (bt == STDERR_FILENO)
		__putchar = putchar_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	cur = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{

		if (_abs_ / index)
		{
			__putchar('0' + cur / index);
			count++;
		}
		cur %= index;
	}
	__putchar('0' + cur);
	count++;
	return (count);
}
/**
 * change_base - Converter function
 * @num: Number
 * @base: Base
 * @flags: argument flags
 *
 * Return: String
 */
char *change_base(long int num, int base, int flags)
{
	char number_sign = 0;
	char *point;
	unsigned long number = num;

	static char *array;
	static char buffer[50];

	if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		number = -num;
		number_sign = '-';
	}
	array = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &buffer[49];
	*point = '\0';
	do {
		*--point = array[number % base];
		number /= base;
	} while (number != 0);
	if (number_sign)
		*--point =number_sign;
	return (point);
}

/**
 * handle_comments - Function replaces first instance of '#' with '\0'
 * @buf: Address of the string
 *
 * Return: 0;
 */

void handle_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
