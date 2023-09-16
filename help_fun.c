#include "btshell.h"

/**
 * check_command - Searches for a command in PATH or the current directory
 * @array: A pointer struct
 *
 * Return: void
 */
void check_command(info_q *array)
{
	char *path = NULL;
	int i, word_count;

	array->path = array->argv[0];
	if (array->lc_flag == 1)
	{
		array->lines++;
		array->lc_flag = 0;
	}

	for (i = 0, word_count = 0; array->arg[i]; i++)
		if (!is_delimiter(array->arg[i], " \t\n"))
			word_count++;

	if (!word_count)
		return;

	path = check_file_in_path(array, _getenv(array, "PATH="), array->argv[0]);
	if (path)
	{
		array->path = path;
		create_process(array);
	}
	else
	{
		if ((from_terminal(array) || _getenv(array, "PATH=") || array->argv[0][0] == '/') && is_executable(array, array->argv[0]))
			create_process(array);
		else if (*(array->arg) != '\n')
		{
			array->status = 127;
			print_error(array, "not found\n");
		}
	}
}

/**
 * create_process - Forks a new process to run the command
 * @array: Pointer struct
 *
 * This function forks a new process and runs the command specified by the
 * @info->argv array. The new process runs in a separate memory space and
 * shares environment variables with the parent process.
 *
 * Return: void
 */
void create_process(info_q *array)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return;
	}

	if (cpid == 0)
	{
		if (execve(array->path, array->argv, get_environ(array)) == -1)
		{
			free_info(array, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(array->status));
		if (WIFEXITED(array->status))
		{
			array->status = WEXITSTATUS(array->status);

			if (array->status == 126)
				print_error(array, "Permission denied\n");
		}
	}
}
