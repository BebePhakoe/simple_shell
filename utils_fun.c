#include "btshell.h"

/**
 * from_terminal - returns true if shell is interactive mode
 * @array: struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int from_terminal(info_t *array)
{
	return (isatty(STDIN_FILENO) && array->bt_read <= 2);
}

/**
 * handle_built - finds an already built in command
 * @array: the array that holds info_q values
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int handle_built(info_q *array)
{
	int i, builtin_return_value = -1;

	builtin_commands builtints[] = {
		{"cd", handle_cd},
		{"env", _printenv},
		{"exit", handle_exit},
		{"help", handle_help},
		{"alias", handle_alias},
		{"setenv", check_setenv},
		{"history", handle_history},
		{"unsetenv", check_unsetenv},
		{NULL, NULL}};

	for (i = 0; builtints[i].type; i++)
		if (_strcmp(array->argv[0], builtints[i].type) == 0)
		{
			array->lines++;
			builtin_return_value = builtints[i].func(array);
			break;
		}
	return (builtin_return_value);
}
