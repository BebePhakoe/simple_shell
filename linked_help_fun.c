#include "btshell.h"
/**
 * _listlen - Gets the length of the list
 * @h: Pointer
 *
 * Return: Size of list.
 */
size_t _listlen(const list_s *h)
{
	size_t index = 0;

	while (h)
	{
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * list_to_vector - returns an array of strings of the list->str
 * @head: Pointer
 *
 * Return: Array of strings.
 */

char **list_to_vector(list_s *head)
{
	list_s *node = head;
	size_t index = _listlen(head), k;
	char **strs;
	char *str;

	if (!head || !index)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));

	if (!strs)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < index; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[index] = str;
	}
	strs[index] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_s linked list
 * @h: Pointer
 *
 * Return: Size of list
 */

size_t print_list(const list_s *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(change_base(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_str_start - Returns node whose string starts with prefix
 * @node: Pointer
 * @prefix: String to check
 * @c: the next character after prefix to check
 *
 * Return: match node or null
 */

list_s *node_str_start(list_s *node, char *prefix, char c)
{
	char *point = NULL;

	while (node)
	{
		point = starts_with(node->str, prefix);
		if (point && ((c == -1) || (*point == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets index of node
 * @head: Pointer to list head
 * @node: Pointer to the node
 *
 * Return: -1 or index of node
 */

ssize_t get_node_index(list_s *head, list_s *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
