#include "btshell.h"
/**
 * main - entry point
 * @argc: number of agurments
 * @argv: value of arguments
 *
 * Return: 0(Success), 1(Failure)
 */

int main(int argc, char **argv)
{
	info_t info[] = {INI_INFO};
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
				puts_err(argv[1]); /* function 13 */
				putchar_err('\n');
				putchar_err(NEG_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->bt_read = bt;
	}

	gather_env(info); /* function 13 */
	read_history(info); /* function 12 */
	shell_main(info, argv);

	return (EXIT_SUCCESS);
}

/**
 * shell_main - Entry point
 * @info: Pointer to an info_t for shell information
 * @av: Array of strings containing arguments to the shell
 *
 * Return: Executed builtin command
 */
int shell_main(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(info);

		if (from_terminal(info))
			_puts("$ ");

		putchar_err(NEG_ONE); /* function 9 */
		read_result = get_input(info); /* function 8 */

		if (read_result != -1)
		{
			ini_info(info, av);
			builtin_return_value = handle_builtin(info); /* function 6 */

			if (builtin_return_value == -1)
				check_command(info); /* function 5 */
		}

		else if (from_terminal(info))
			_putchar('\n');

		free_info(info, 0);
	}
	create_history(info); /* function 2 */

	free_info(info, 1);
	if (!from_terminal(info) && info->status)
		exit(info->status);

	if (builtin_return_value == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return (builtin_return_value);
}
