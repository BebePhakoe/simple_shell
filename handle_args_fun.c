#include "btshell.h"

/**
 * is_executable - Responsible for  determining
 *  if a file can be executed
 * @array: Struct
 * @path: Path to file
 *
 * Return: 1 if true, 0 otherwise
 */
bool is_executable(info_q *array, char *path)
{
	struct stat st;

	(void)array;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (true);
	}
	return (false);
}

/**
 * dup_chars - Responsible for duplicating characters
 * @pathstr: Path string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int index = 0, k = 0;

	for (k = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			buffer[k++] = pathstr[index];
	buffer[k] = 0;
	return (buffer);
}

/**
 * check_file_in_path - finds this cmd in the PATH string
 * @array: Struct
 * @pathstr: Path string
 * @cmd: cmd to find
 *
 * Return: Full path of cmd if found or NULL
 */
char *check_file_in_path(info_q *array, char *pathstr, char *cmd)
{
	int index = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(array, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			path = dup_chars(pathstr, current_position, index);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(array, path))
				return (path);
			if (!pathstr[index])
				break;
			current_position = index;
		}
		index++;
	}
	return (NULL);
}
