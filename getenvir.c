#include "shell.h"

/**
 * _getenvir: gets/returns the str array of my env't.
 * @info:  potential args contained in the struct
 *
 * Return: 0 Always
 */
char **_getenvir(info_t *info)
{
	if (!info->envir || info->env_changed)
	{
		info->envir = to_str(info->env);
		info->env_changed = 0;
	}

	return (info->envir);
}

/**
 * unset_env: delete an env'nt variable
 * @info:  containing args contained in struct.
 *
 *  Return: 10 if not del, 1 on delete.
 * @var:  str env'nt variable property.
 */

int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env: new envnt var initialized
 *
 * @info:  potential args contained in struct.
 *
 * @var - str env'nt variable property
 * @value:  str env'nt variable value.
 *  Return:  0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_node_endplus(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
