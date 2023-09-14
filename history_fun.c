#include "btshell.h"
/**
 * read_hist - Reads and gets history of file
 * @array: Parameter struct
 *
 * Return: A string containing history file
 */

char *read_hist(info_q *array)
{
	char *buf, *dir;

	dir = _getenv(array, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE_NAME);
	return (buf);
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
	write_char(NEG_ONE, bt);
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
	int i, last = 0, linecount = 0;
	ssize_t bt, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *file_name = read_hist(array);

	if (!file_name)
		return (0);

	bt = open(file_name, O_RDONLY);
	free(file_name);
	if (bt == -1)
		return (0);
	if (!fstat(bt, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(bt, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(bt);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			update_history(array, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		update_history(array, buf + last, linecount++);
	free(buf);
	array->hist_lines = linecount;
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
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (array->hist_lines = j);
}
