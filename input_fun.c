#include "shell.h"

/**
 * input_buf - The buffers commands
 * @array:The parameter struct
 * @buf: The address of buffer
 * @len: The address of len var
 *
 * Return: Bytes
 */
ssize_t input_buf(info_q *array, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(array, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			array->lc_flag = 1;
			handle_comments(*buf); /*function 1*/
			update_history(array, *buf, array->hist_lines++);
			{
				*len = r;
				info->sep_buff = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - The line that gets minus the newline
 * @array: The parameter struct
 *
 * Return: Bytes
 */
ssize_t get_input(info_q *array)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(array->arg), *p;

	_putchar(NEGATIVE_ONE);
	r = input_buf(array, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(array, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(array, buf, &j)) /*function 2*/
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->sep_buff_kind = REG_FLAG;
		}
		*buf_p = p;
		return (_strlen(p)); /*function 3*/
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads a buffer
 * @array: The parameter struct
 * @buf: The buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_q *array, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(array->bt_read, buf, BUFFER_SIZE_READ);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Function to get the next line of input from STDIN
 * @array: The parameter struct
 * @ptr: The address of the pointer to buffer,
 * NULL or pre-allocated
 * @length: The size of pre-allocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_q *array, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE_READ];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(array, buf, &len); /* function 6 */
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n'); /* function 5 */
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1); /* function 4 */
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i); /* function 3 */
	else
		_strncpy(new_p, buf + i, k - i + 1); /* function 2 */

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_sigint - It blocks the ctrl-C
 * @sig_num: Number signal
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ "); /* function 1 */
	_putchar(NEG_ONE);
}
