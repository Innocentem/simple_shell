#include "shell.h"

/**
 * my_envir - current env'nt gets prntd.
 * @info: potential args are contained in struct
 *
 * Return 0 Always.
 */
int my_envir(info_t *info)
{
	_list_stripr(info->env);
	return (0);
}

/**
 * get_envir: value of env'nt var is got.
 * @info: potential args contained in struct
 * @name: name of environment variable.
 *
 * Return: value
 */

char *get_envir(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv: new env'nt variable is initialized.
 *
 * @info: potential args contained in struct
 *
 *  Return: 0 Always
 */

int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_laput("number of args not correct\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv: deletes env'nt variable.
 * @info: potential args contained in struct
 *
 * Return: 0 Always
 */

int my_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_laput("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * _populate_envlist: env'nt linked list is populated.
 * @info: potential args contained in struct.
 *
 * Return: 0 Always
 */
int _populate_envlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_node_endplus(&node, environ[i], 0);
	info->env = node;
	return (0);
}
