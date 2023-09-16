#include "btshell.h"
/**
 * from_terminal - Returns true if shell is in interactive mode
 * @array: The struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int from_terminal(info_q *array)
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
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string else converted integer
 */

int _atoi(char *s)
{
	int index, number_sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; s[index] != '\0' && flag != 2; index++)
	{
		if (s[index] == '-')
			number_sign *= -1;
		if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (number_sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delimiters: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

bool is_delimiter(char c, char *delimiters)
{
	int k;

	for (k = 0; delimiters[k]; k++)
		if (c == delimiters[k])
			return (true);
	return (false);
}
