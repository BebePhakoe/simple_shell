#include "btshell.h"

/**
 * clear_info - To initializes the info_q struct
 * @info: The adress for struct
 */
void clear_info(info_q *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - To initializes the info_q struct
 * @info: The adress for struct
 * @av: The argument vector
 */
void set_info(info_q *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t"); /* function 7 */
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg); /* function 1*/
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		change_alias(info); /* function 6 */
		change_v(info); /* function 8 */
	}
}
/**
 * free_info - Frees the info_q struct
 * @info: The adress for struct
 * @all: True if the info is free
 */
void free_info(info_q *info, int all)
{
	free_vector(info->argv); /* function 2*/
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env)); /* function 3 */
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_vector(info->environ);
		info->environ = NULL;
		bfree((void **)info->sep_buff); /* function 4*/
		if (info->bt_read > 2)
			close(info->bt_read);
		_putchar(NEGATIVE_ONE);
	}
}
