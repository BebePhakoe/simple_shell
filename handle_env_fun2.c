#include "btshell.h"

/**
 * _getenv - Responsible for getting environ value
 * @array: Function pointer,
 * @name: env var name
 *
 * Return: Value
 */

char *_getenv(info_q *array, const char *name)
{
	char *p;
	list_s *node = array->env;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * check_setenv - Checks if an environment variable has been set.
 * @array: Function pointer, allowing for a consistent function prototype
 *
 * Return: 0 if set, else 1.
 */

int check_setenv(info_q *array)
{
	if (array->argc != 3)
	{
		puts_err("Incorrect number of arguements\n");
		return (1);
	}

	if (_setenv(array, array->argv[1], array->argv[2]))
		return (0);
	return (1);
}

/**
 * check_unsetenv - Removes an environment variable
 * @array: Function pointer, allowing for a consistent function prototype
 * Return: Always 0
 */
int check_unsetenv(info_q *array)
{
	int i;

	if (array->argc == 1)
	{
		puts_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= array->argc; i++)
		_unsetenv(array, array->argv[i]);

	return (0);
}

/**
 * gather_env - Responsible populating env linked list
 * @array: Function pointer, allowing for a consistent function prototype
 * Return: Always 0
 */
int gather_enviroment(info_q *array)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	array->env = node;
	return (0);
}

/**
 * _printenv - Prints the current environment
 * @array: Function pointer, allowing for a consistent function prototype
 * Return: Always 0
 */
int _printenv(info_q *array)
{
	print_list_str(array->env);
	return (0);
}
