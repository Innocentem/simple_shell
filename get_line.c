#include "shell.h"

/**
 * buf_in - buffer commands
 * @info:  structure parameter
 * @buf:  buffer address
 * @len:  len var address
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
			{
				*len = t;
				info->cmd_buf = buf;
			}
		}
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
	r = input_buf(info, &buf, &len);
	if (t == -1) 
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
	return (t);
}

/**
 * read_buf:  a buffer is read
 * @info:  structure parameter
 * @buf: buffer
 * @s: size
 *
 * Return: t
 */
ssize_t read_buf(info_t *info, char *buf, size_t *s)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - calls or gets the next line of input from Standard input
 * @info:  structure parameter.
 * @ptr:  pointer to buffer address
 * @length: length of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - counters ctrl-C
 * @sig_num:  signal number 
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
