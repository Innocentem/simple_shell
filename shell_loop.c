#include "shell.h"

/**
 * hsh - the main loop shell
 * @info:  return info structure & parameter
 * @av:  vector of argument from main()
 *
 * Return: 1 on error, 0 on success,
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_clear(info);
		if (intuitive(info))
			_puts("my$: ");
		laputchar(BUF_FLUSH);
		r = inpt_gt(info);
		if (r != -1)
		{
			info_set(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (intuitive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!intuitive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_inbuilt - locates a builtin cmd
 * @info:  return information structure
 *
 * Return: 0 if builtin execute is a success,
 * 	-1 if builtin not found,
 * 	1 if builtin is found but not a success,
 * 	2 if builtin is signaling exit()
 */

int find_inbuilt(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table inbuilttbl[] = {
		{"exit", exiter},
		{"env", my_envir},
		{"help", _help},
		{"history", _hstry},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", _cdr},
		{"alias", _myal},
		{NULL, NULL}
	};

	for (i = 0; inbuilttbl[i].type; i++)
		if (_strcmp(info->argv[0], inbuilttbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = inbuilttbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd: locates a command PATH.
 * @info: return information structure
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!if_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, get_envir(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((intuitive(info) || get_envir(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			errprnt(info, "not found\n");
		}
	}
}

/**
 * fork_cmd: forks an executed thread to run commd
 * @info:  return infor struct
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _getenvir(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				errprnt(info, "Permission not granted\n");
		}
	}
}
