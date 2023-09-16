#include "btshell.h"
/**
 * read_hist - Reads and gets history of file
 * @array: Parameter struct
 *
 * Return: A string containing history file
 */

char *read_hist(info_q *array)
{
	char *buffer, *point;

	point = _getenv(array, "HOME=");
	if (!point)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(point) + _strlen(HIST_FILE_NAME) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, point);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE_NAME);
	return (buffer);
}

/**
 * create_history - Creates file, or appends to an existing file
 * @array: Parameter struct
 *
 * Return: 1 on Success, else -1
 */
int create_history(info_q *array)
{
	ssize_t bt;
	char *filename = read_hist(array);
	list_s *node = NULL;

	if (!filename)
		return (-1);

	bt = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (bt == -1)
		return (-1);
	for (node = array->history; node; node = node->next)
	{
		write_chars(node->str, fd);
		write_char('\n', bt);
	}
	write_char(NEGATIVE_ONE, bt);
	close(bt);
	return (1);
}

/**
 * hist_read - Reads history of file
 * @array: Parameter struct
 *
 * Return: Hist_lines on success, 0 otherwise
 */
int hist_read(info_q *array)
{
	int index, l = 0, count = 0;
	ssize_t bt, rdlen, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = read_hist(array);

	if (!file_name)
		return (0);

	bt = open(file_name, O_RDONLY);
	free(file_name);
	if (bt == -1)
		return (0);
	if (!fstat(bt, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (0);
	rdlen = read(bt, buffer, size);
	buffer[size] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(bt);
	for (index = 0; index < size; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			update_history(array, buffer + l, count++);
			l = index + 1;
		}
	if (l != index)
		update_history(array, buffer + l, count++);
	free(buffer);
	array->hist_lines = count;
	while (array->hist_lines-- >= HIST_SIZE_MAX)
		delete_node_at_index(&(array->history), 0);
	renumber_history(array);
	return (array->hist_lines);
}

/**
 * update_history - Responsible for adding entry to a history linked list
 * @array: Arguments for a function pointer,
 * @buf: Buffer
 * @linecount: History linecount
 *
 * Return: Always 0
 */
int update_history(info_q *array, char *buf, int linecount)
{
	list_s *node = NULL;

	if (array->history)
		node = array->history;
	add_node_end(&node, buf, linecount);

	if (!array->history)
		array->history = node;
	return (0);
}

/**
 * renumber_history - Responsible for renumbering
 * the history linked list
 * @array: Arguments for a function pointer
 *
 * Return: Hist_lines
 */
int renumber_history(info_q *array)
{
	list_s *node = array->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (array->hist_lines = k);
}
