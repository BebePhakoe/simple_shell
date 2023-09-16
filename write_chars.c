#include "btshell.h"

/**
 * write_chars - prints an input string
 * @str: string to printed
 * @bt: the filedescriptor
 *
 * Return: the number of chars put
 */
int write_chars(char *str, int bt)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += write_char(*str++, bt);
	}
	return (index);
}

/**
 * change_base - a clone of itoa function
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
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
		*--point = number_sign;
	return (point);
}

/**
 * handle_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: 0;
 */

void handle_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
