#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define BUF_FLUSH -1
char buf[20];
snprintf(buf, sizeof(buf), "%d", BUF_FLUSH);
write(fd, buf, strlen(buf));

/* cmmnd chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

void for_buf(int fd)
{
	char buf[64];
snprintf(buf, sizeof(buf), "%d", BUF_FLUSH);
write(fd, buf, strlen(buf));
}

extern char **environ;


/**
 * struct liststr - this is thesingly linked list
 * @num: no field
 * @str: a string
 * @next: this actually points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - this is a content of pseudo-arguements to pass into a function,
 * it allows uniform prototype for pointer structure function
 * @arg: a string generated from getline containing arguements
 * @argv: strings array generated from argument
 * @path: a path of string for the current cmd
 * @argc:  count of arguments
 * @line_count:  counts error
 * @err_num:  error code for exiting()s
 * @linecount_flag: if on just count this inputed line
 * @fname:  filename of program
 * @env: list linked of local copy of environment
 * @environ:  modified copy of custom of environ from LL environment
 * @history: the node of history
 * @alias: node of alias
 * @env_changed: on if environment is changed
 * @status:  return status of the last executed'd command
 * @cmd_buf:  pointer address to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd to read line input
 * @histcount:  number count of history line
 */
typedef struct passinfo
{
	char *arg;
	char *info;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char *cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - containing a builtin strng and related function
 * @type: the builtin cmd flag
 * @func: the funct
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_error.c */
void _laput(char *);
int laputchar(char);
int put_a(char c, int fd);
int la_puta(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *str_chr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_inter.c */
int intuitive(info_t *);
int if_delim(char, char *);
int _alphachk(int);
int int_str(char *);

/* toem_errorfile.c */
int erri(char *);
void errprnt(info_t *, char *);
int dprint(int, int);
char *fn_cnvt(long int, int, int);
void _comrmv(char *);

/* toem_inbuilt.c */
int exiter(info_t *);
int _cdr(info_t *);
int _help(info_t *);

/* toem__builtin.c */
int _hstry(info_t *);
int _myal(info_t *);

/*toem_get_line.c */
ssize_t inpt_gt(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t input_buf(info_t *info, char **buf, size_t *len);

/* toem_getinfo.c */
void info_clear(info_t *);
void info_set(info_t *, char **);
void info_free(info_t *, int);
void remove_comments(char *str);

/* toem_envir.c */
char *get_envir(info_t *, const char *);
int my_envir(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int _populate_envlist(info_t *);

/* toem_getenvir.c */
char **_getenvir(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem__list.c */
list_t *_nodeplus(list_t **, const char *, int);
list_t *_node_endplus(list_t **, const char *, int);
size_t _list_stripr(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem__lists.c */
size_t len_list(const list_t *);
char **to_str(list_t *);
size_t list_pr(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
