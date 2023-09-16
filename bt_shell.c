#include "btshell.h"
/**
 * main - Main function
 * @argc: Number of parameters
 * @argv: Value of parameters
 *
 * Return: 0(Success), 1(Failure)
 */

int main(int argc, char **argv)
{
< < < < < < < HEAD
	info_q array[] = {INI_INFO};
= = = = = = =
	info_q array[] = {INI_INFO};
> > > > > > > d37278aab696289dd5b41bfe06e42d7829238c74
	int bt = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(bt)
		: "r"(bt));

	if (argc == 2)
	{
		bt = open(argv[1], O_RDONLY);
		if (bt == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				puts_err(argv[0]);
				puts_err(": 0: Can't open ");
				puts_err(argv[1]);
				putchar_err('\n');
				putchar_err(NEGATIVE_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}
		array->bt_read = bt;
	}

	gather_enviroment(array); /* function 13 */
	main_history(array);
	shell_main(array, argv);

	return (EXIT_SUCCESS);
}

/**
 * shell_main - Entry point
 * @array: Pointer to an info_q for shell information
 * @av: Array of strings containing arguments to the shell
 *
 * Return: Executed builtin command
 */

int shell_main(info_q *array, char **av)
{
< < < < < < < HEAD
	ssize_t read_result = 0;
> > > > > > > d37278aab696289dd5b41bfe06e42d7829238c74
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(array);

		if (from_terminal(array))
			_puts("$ ");

		putchar_err(NEGATIVE_ONE);
		read_result = get_input(array);

		if (read_result != -1)
		{
			ini_info(array, av);
			builtin_return_value = handle_builtin(array);

			if (builtin_return_value == -1)
				check_command(array);
		}
		else if (from_terminal(array))
			_putchar('\n');

		free_info(array, 0);
	}
	create_history(array);
	free_info(array, 1);
	if (!from_terminal(array) && array->status)
		exit(array->status);

	if (builtin_return_value == -2)
	{
		if (array->error_code == -1)
			exit(array->status);
		exit(array->error_code);
	}
	return (builtin_return_value);
}
