#include "shell.h"

/**
 * _hstry: the history list beginning at 0
 * @info: potential arguments of the structure are here
 *  Return: 0 Always
 */
int _hstry(info_t *info)
{
	len_list(info->history);
	return (0);
}

/**
 * unset_al:  string is set to allias
 * @info: parameter struct
 * @str: alias of strings
 *
 * Return: 0 on success, 1 on error
 */
int unset_al(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_al - string set to alias
 * @info: structure of parameters
 * @str: alias of strings
 *
 * Return: 0 on success, 1 on error
 */
int set_al(info_t *info, char *str)
{
	char *q;

	q = strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_al(info, str));

	unset_al(info, str);
	return (_node_endplus(&(info->alias), str, 0) == NULL);
}

/**
 * print_al - string alias is printed
 * @node: node of alias
 *
 * Return: 0 on success, 1 for error
 */
int print_al(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myal: immitates the alias builtin
 * @info - potential arguments of the structure
 *
 *  Return: Always 0
 */
int _myal(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_al(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');
		if (p)
			set_al(info, info->argv[i]);
		else
			print_al(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
