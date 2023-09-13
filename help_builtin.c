#include "btshell.h"

/**
 * handle_exit - Shell exit
 * @array: Arguments for a function pointer, that allow for function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int handle_exit(info_q *array)
{
	int exitcheck;

	if (array->argv[1])
	{
		exitcheck = err_num(array->argv[1]);
		if (exitcheck == -1)
		{
			array->status = 2;
			print_error(array, "Illegal number: ");
			puts_err(array->argv[1]);
			putchar_err('\n');
			return (1);
		}
		array->error_code = err_num(array->argv[1]);
		return (-2);
	}
	array->error_code = -1;
	return (-2);
}
/**
 * handle_cd - Responsible for changes to the current directory
 * @array: Arguments for a function pointer, that allow for function prototype
 * Return: 0
 */

int handle_cd(info_q *array)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!array->argv[1])
	{
		dir = _getenv(array, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(array->argv[1], "-") == 0)
	{
		if (!_getenv(array, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(array, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(array->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(array, "can't cd to ");
		puts_err(array->argv[1]), putchar_err('\n');
	}
	else
	{
		_setenv(array, "OLDPWD", _getenv(array, "PWD="));
		_setenv(array, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * handle_help - Responsible for printing a message
 * for a function not to be implemented
 * @array: Arguments for a function pointer, that allow for function prototype
 * Return: 0
 */

int handle_help(info_q *array)
{
	char **arg_array;

	arg_array = array->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

/**
 * handle_history - Responsible for displaying the history list
 * @array: Arguments for a function pointer, that allow for function prototype
 *	Return: Always 0
 */
int handle_history(info_q array)
{
	print_list(array->history);

	return (0);
}
