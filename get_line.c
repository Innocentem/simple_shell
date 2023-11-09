#include "shell.h"

/**
 * buf_in: buffer comnds.
 * @info: struct parameter
 * @buf: buffer address.
 * @len: len var address
 *
 * Return: bytes read
 */

ssize_t buf_in(info_t *info, char **buf, size_t *len)
{
	ssize_t t = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
	}
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	t = getline(buf, &len_p, stdin);
#else
	t = _getline(info, buf, &len_p);
#endif
	if (t > 0)
	{
		if ((*buf)[t - 1] == '\n')
		{
			(*buf)[t - 1] = '\0';
			t--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		*len = t;
		info->cmd_buf = *buf;
	}
	return (t);
}

/**
 * inpt_gt: calls or gets a line w/out the newline
 * @info: structure parameter
 *
 * Return: bytes read
 */
ssize_t inpt_gt(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buf_in(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

