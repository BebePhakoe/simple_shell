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

#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEGATIVE_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define BAS_CHANGE_LOWER 1
#define BAS_CHANGE_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE_NAME ".ss_history"
#define HIST_SIZE_MAX 4096

#define INI_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct ListNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} list_s;

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

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_q *);
} builtin_commands;

int shell_main(info_q *info, char **av);
int from_terminal(info_q *info);
void clear_info(info_q *info);
void ini_info(info_q *info, char **av);
void free_info(info_q *info, int all);
ssize_t input_buf(info_q *info, char **buf, size_t *len);
void handle_sigint(__attribute__((unused)) int sig_num);
int _getline(info_q *info, char **ptr, size_t *length);
ssize_t read_buf(info_q *info, char *buf, size_t *i);
ssize_t read_buf(info_q *info, char *buf, size_t *i);
int handle_built(info_q *array);
char *read_hist(info_q *array);
int create_history(info_q *array);
int main_history(info_q *array);
int update_history(info_q *array, char *buf, int linecount);
int renumber_history(info_q *array);
int write_chars(char *str, int bt);
ssize_t get_node_index(list_s *, list_s *);
char **split_string(char *str, char *separators, size_t *word_count);
int words_count(char *str, char *separators, unsigned int *arr);
void set_zeros(unsigned int *arr, size_t size);
void set_nulls(char *arr, size_t size);
bool is_delimiter(char c, char *delimiters);
list_s *add_node_start(list_s **head, const char *str, int num);
list_s *add_node_end(list_s **head, const char *str, int num);
list_s *node_str_start(list_s *, char *, char);
size_t print_list_str(const list_s *);
size_t _listlen(const list_s *);
size_t print_list(const list_s *);
ssize_t get_input(info_q *);
int delete_node_at_index(list_s **, unsigned int);
bool is_chain(info_q *, char *, size_t *);
int change_alias(info_q *);
int change_v(info_q *);
int change_string(char **, char *);
int print_dec(int, int);
int gather_env(info_q *);
void handle_comments(char *);
void free_list(list_s **);
void check_chain(info_q *info, char *buf, size_t *p, size_t i, size_t len);
int handle_builtin(info_q *);
bool is_executable(info_q *, char *);
int loophsh(char **);
int bfree(void **);
void free_vector(char **);
void print_error(info_q *, char *);
void check_command(info_q *);
void create_process(info_q *);
char **get_environ(info_q *);
char **strtow(char *, char *);
char **list_to_vector(list_s *);
void _puts(char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(info_q *, const char *);
char *starts_with(const char *, const char *);
char *dup_chars(char *, int, int);
char *check_file_in_path(info_q *info, char *pathstr, char *cmd);
char *change_base(long int, int, int);
int _printenv(info_q *);
int check_setenv(info_q *);
int check_unsetenv(info_q *);
int _unsetenv(info_q *, char *);
int _setenv(info_q *, char *, char *);
int handle_exit(info_q *);
int handle_cd(info_q *);
int handle_help(info_q *);
int handle_history(info_q *);
int handle_alias(info_q *);
int _putchar(char);
int _isalpha(int);
int _atoi(char *);
int write_char(char c, int bt);
int write_chars(char *str, int bt);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int putchar_err(char);
void puts_err(char *);
int err_num(char *);
#endif
