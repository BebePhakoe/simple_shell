#include "btshell.h"

/**
 * from_terminal - Returns true if shell is in interactive mode
 * @info: The struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int from_terminal(info_q *info)
{
	return (isatty(STDIN_FILENO) && info->bt_read <= 2);
}
