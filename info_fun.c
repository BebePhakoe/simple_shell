#include "btshell.h"

/**
 * clear_info - To initializes the info_q struct
 * @info: The adress for struct
 */
void clear_info(info_q *array)
{
	array->arg = NULL;
	array->argv = NULL;
	array->path = NULL;
	array->argc = 0;
}

/**
 * free_info - Frees the info_q struct
 * @array: The adress for struct
 * @all: True if the info is free
 */
void free_info(info_q *array, int all)
{
	free_vector(array->argv); /* function 2*/
	array->argv = NULL;
	array->path = NULL;
	if (all)
	{
		if (!array->sep_buff)
			free(array->arg);
		if (array->env)
			free_list(&(array->env)); /* function 3 */
		if (array->history)
			free_list(&(array->history));
		if (array->alias)
			free_list(&(array->alias));
		free_vector(array->environ);
		array->environ = NULL;
		bfree((void **)array->sep_buff); /* function 4*/
		if (array->bt_read > 2)
			close(array->bt_read);
		_putchar(NEGATIVE_ONE);
	}
}
