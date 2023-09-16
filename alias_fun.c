#include "btshell.h"

/**
 * unset_alias - Responsible for setting the alias to string
 * @array: Parameter struct
 * @str: String
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_q *array, char *str)
{
	char *point, ch;
	int return_value;

	point = _strchr(str, '=');
	if (!point)
		return (1);
	ch = *point;
	*point = 0;
	return_value = delete_node_at_index(&(array->alias),
			get_node_index(array->alias, node_str_start(array->alias, str, -1)));
	*point = ch;
	return (return_value);
}

/**
 * set_alias - Responsible for setting the alias to string
 * @array: Parameter struct
 * @str: String
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_q *array, char *str)
{
	char *point;

	point = _strchr(str, '=');
	if (!point)
		return (1);
	if (!*++point)
		return (unset_alias(array, str));

	unset_alias(array, str);
	return (add_node_end(&(array->alias), str, 0) == NULL);
}

/**
 * print_alias - Responsible for printing an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *point = NULL, *another = NULL;

	if (node)
	{
		point = _strchr(node->str, '=');
		for (another = node->str; another <= point; another++)
			_putchar(*another);
		_putchar('\'');
		_puts(point + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias - Responsible for mimicing the alias builtin (man alias)
 * @array: Function pointer, allowing for a consistent function prototype
 * Return: Always 0
 */
int handle_alias(info_q *array)
{
	int i = 0;
	char *point = NULL;
	list_s *node = NULL;

	if (array->argc == 1)
	{
		node = array->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; array->argv[i]; i++)
	{
		point = _strchr(array->argv[i], '=');
		if (point)
			set_alias(array, array->argv[i]);
		else
			print_alias(node_str_start(array->alias, array->argv[i], '='));
	}
	return (0);
}

/**
 * change_alias - Responsible for replacing
 * an aliases in the tokenized string
 * @array: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_q *array)
{
	int index;
	list_s *node;
	char *point;

	for (index = 0; index < 10; index++)
	{
		node = node_str_start(array->alias, array->argv[0], '=');
		if (!node)
			return (0);
		free(array->argv[0]);
		point = _strchr(node->str, '=');
		if (!point)
			return (0);
		point = _strdup(point + 1);
		if (!point)
			return (0);
		array->argv[0] = point;
	}

	return (1);
}
