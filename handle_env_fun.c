#include "btshell.h"

/**
 * get_environ - Returns a copy of the
 * environment variables as an array of strings.
 * @array: Struct, used to maintain constant function prototype.
 * Return: Environment variables
 */

char **get_environ(info_q *array)
{
	if (!array->environ || array->env_changed)
	{
		array->environ = list_to_vector(array->env);
		array->env_changed = 0;
	}
	return (array->environ);
}

/**
 * _setenv - Adds or updates an environment variable.
 * @array: Struct, used to maintain constant function prototype.
 * @var: Name of the environment variable to add or update.
 * @value: Value of the environment variable to add or update.
 * Return: 0 if the environment variable is
 * successfully added or updated, else 1.
 */

int _setenv(info_q *array, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = array->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			array->env_changed = 1;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(array->env), buf, 0);
	free(buf);
	array->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Removes an environment variable.
 * @array: Structure used to maintain constant function prototype.
 * @var: The name of the environment variable to remove.
 * Return: 1 if the environment variable was successfully removed, else 0.
 */
int _unsetenv(info_q *array, char *var)
{
	list_s *node = array->env;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			array->env_changed = delete_node_at_index(&(array->env), index);

			index = 0;
			node = array->env;
			continue;
		}

		node = node->next;
		index++;
	}

	return (array->env_changed);
}
