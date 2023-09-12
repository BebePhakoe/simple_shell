#ifndef BTSHELL_H
#define BTSHELL_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INI_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

/**
 * struct InfoNode - A function pointer that contains simulated arguments
 * @arg: Generated from getline that holds arguments that returns a string
 * @argv: AN array of strings generated from @arg
 * @path: The path string
 * @argc: The number of arguments
 * @lines: The number of errors
 * @error_code: The exit() error code
 * @lc_flag: A flag indicating line of input and should it be counted
 * @prog_name: The name of the program's file
 * @env: A linked list that represents a local copy of the environment
 * @environ: A copy of the environ from the linked list env
 * @history: The node for the command history
 * @alias: The node for the command alias
 * @env_changed: A flag that indicates if the environ has been changed
 * @status: The return status of the most recent executed command
 * @sep_buff: The address of the pointer to sep_buff
 * @sep_buff_kind: The type of command buffer (CMD_type ||, &&, ;)
 * @bt_read: The file descriptor for reading
 * @hist_lines: The number of lines in the history
 */

typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **sep_buff;
	int sep_buff_kind;
	int bt_read;
	int hist_lines;
} info_q;

int shell_main(info_q *info, char **av);
int from_terminal(info_q *info);
void clear_info(info_q *info);
void ini_info(info_q *info, char **av);
void free_info(info_q *info, int all);
ssize_t input_buf(info_q *info, char **buf, size_t *len);
void handle_sigint(__attribute__((unused)) int sig_num);
int _getline(info_q *info, char **ptr, size_t *length);
< < < < < < < HEAD
ssize_t read_buf(info_q *info, char *buf, size_t *i);
= = = = = = =
ssize_t read_buf(info_q *info, char *buf, size_t *i);
int handle_built(info_q *array);
> > > > > > > d37278aab696289dd5b41bfe06e42d7829238c74

#endif
