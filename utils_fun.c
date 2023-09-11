#include "btshell.h"

/**
 * from_terminal - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int from_terminal(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->bt_read <= 2);
}
