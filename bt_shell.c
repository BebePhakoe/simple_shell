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
				puts_err(argv[1]);
				putchar_err('\n');
				putchar_err(NEG_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->bt_read = bt;
	}

	gather_env(info);
	read_history(info);
	shell_main(info, argv);

	return (EXIT_SUCCESS);
}

/**
 * shell_main - main control for the shell program
 * @info: pointer to an info_s struct containing shell information
 * @av: array of strings containing arguments to the shell
 *
 * Return: the status of the last executed builtin command
 */
int shell_main(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(info);

		/* Display the shell prompt if in interactive mode */
		if (from_terminal(info))
			_puts("$ ");

		putchar_err(NEG_ONE);
		read_result = get_input(info);

		/* Handle input if it was successfully read */
		if (read_result != -1)
		{
			ini_info(info, av);
			builtin_return_value = handle_builtin(info);

			/* Check for command execution if not a builtin command */
			if (builtin_return_value == -1)
				check_command(info);
		}

		/* Handle end of input if in from_terminal mode */
		else if (from_terminal(info))
			_putchar('\n');

		free_info(info, 0);
	}

	/* Create and store the history list */
	create_history(info);

	/* Free memory and exit */
	free_info(info, 1);
	if (!from_terminal(info) && info->status)
		exit(info->status);

	/* Handle exit with error */
	if (builtin_return_value == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}

	/* Return the last executed builtin command's status */
	return (builtin_return_value);
}
