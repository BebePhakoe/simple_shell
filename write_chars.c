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
 * ini_info - initializes info_q struct
 * @array: struct address
 * @av: argument vector
 */
void ini_info(info_q *array, char **av)
{
	int i = 0;

	array->prog_name = av[0];
	if (array->arg)
	{
		array->argv = strtow(array->arg, " \t");
		if (!array->argv)
		{
			array->argv = malloc(sizeof(char *) * 2);
			if (array->argv)
			{
				array->argv[0] = _strdup(array->arg);
				array->argv[1] = NULL;
			}
		}
		for (i = 0; array->argv && array->argv[i]; i++)
		{
			array->argc = i;
			change_alias(array);
			change_v(array);
		}
	}
}
